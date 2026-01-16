/*

   --  Client Side 

   --  Created by Tomsa da DtandarS

   --  I want a job man........

*/


#include <master.h>

static size_t max_message = 4096;

static void die(const char *msg)
{
  int err = errno;
  printf("[%d] %c\n", err, *msg);
  abort();
}

static int32_t read_full(int fd, char *buf, size_t n)
{
  while(n > 0)
  {
    ssize_t rv = read(fd, buf, n);
    if ( rv < 0 )
    {
      return -1; // returns error or unexpected EOF
    }
    assert((size_t)rv <= n);
    n -= (size_t)rv;
    buf += rv; 
  }
  return 0;
}

static int32_t write_all(int fd, const char *buf, size_t n)
{
 while ( n > 0)
 {
   int rv = write(fd, buf, n);
   if (rv <= 0)
   {
     return -1;
   }
   assert((ssize_t)rv <= n);
   n -= (size_t)rv;
   buf += rv;
 }
 return 0;
}

static int32_t query(int fd, const char *msg)
{
  uint32_t len =(uint32_t)strlen(msg);
  if (len > max_message )
  {
    return -1;
  }
  //  send request
  char wbuf[4 + max_message];
  memcpy(wbuf, &len, 4);
  memcpy(&wbuf[4], text, len);
  if (int32_t err = write_all(fd, wbuf, 4 + len))
  {
    return err;
  }
  // 4 byte header
  char rbuf[4 + max_message];
  errno = 0;
  int32_t err = read_full(fd, rbuf, 4);
  if (err)
  {
    msg(errno == 0 ? "EOF" : "read() error");
  }
  memcpy(&len, rbuf, 4);
  if (len > max_message)
  {
    msg("message too long");
    return -1;
  }

}


int main(int arg, char* argv[])
{

  int fd = socket(PF_INET, SOCK_STREAM, 0);
  if (fd < 0)
  {
    die("socket()");
  }

  int port = 2005;

  struct sockaddr_in addr = {};
  addr.sin_family = PF_INET;
  addr.sin_port = ntohs(port);
  addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); //INADDR_LOOPBACK is defined as 0x7f000001, which is the address 127.0.0.1.
  int rv = connect(fd, (const struct sockaddr *)&addr, sizeof(addr));
  if (rv)
  {
    die("connect");
  }

  char msg[] = "hello";
  write(fd, msg, strlen(msg));

  char rbuf[64] = {};
  ssize_t n = read(fd, rbuf, sizeof(rbuf) - 1);
  if (n < 0)
  {
    die("read");
  }

  printf("server says %s\n", rbuf);
  close(fd);


  return 0;

}



