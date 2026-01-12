
/*


   - Created by Tomsa da DtandarS

   - 16.12.2025 at 20:44

   - Please hire me please.


*/

#include <master.h>


bool isTrue{true};
static size_t max_message = 4096;

static void msg(const char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

static void do_something(int connfd)
{
  char rbuf[64] = {};
  ssize_t n =  read(connfd, rbuf, sizeof(rbuf) - 1);
  if ( n < 0 )
  {
    msg("read() error");
  }
  printf("client says: %s \n", rbuf);
  char wbuf[]  = "world";
  write(connfd, wbuf, strlen(wbuf));
}

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

static int32_t query(int connfd)
{
  // 4 byte header. no idea what this do.
  char rbuf[4 + max_message];
  errno = 0;
  int32_t err = read_full(connfd, rbuf, 4);
  if (err)
  {
    msg(errno == 0 ? "EOF" : "read() error");
    return err;
  }
  int32_t len = 0;
  memcpy(&len, rbuf, 4);
  if (len > max_message)
  {
    msg("too long");
    return -1;
  }
}


int main(int argv, char** argc)
{

  int port = 2005;
  int fd = socket(PF_INET, SOCK_STREAM, 0);
  /* ============================*/

  //  PF_NET is for IPV4 only 
  //  PF_NET6 is for IPV6 only

  /* ============================*/

  //  SOCK_STREAM is for TCP usage
  //  SOCK_DGRAM is for UDP usage

  /* ============================*/


  int val = 1;
  setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val) );

  /* ============================*/

  //  When setting SO_REUSEADDR to an integer 1 value we have set it is set to true since this option only accepts boolean values. 
  //  If this option is not set the program can not attach it self to the same ip:port after restart.

  /* ============================*/

  sockaddr_in addr = {};
  addr.sin_family = PF_INET;
  addr.sin_port = htons(port); // This is to set the port
  addr.sin_addr.s_addr = htonl(0); //  This sets the IP to 0.0.0.0 
  int rv = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
  if (rv) 
  { die("bind()"); }

  //  To set port you can either use declared variable or set the port manually each time. 
  //  Setting IP address = htonl(0x01020304) 0x01020304 is set to 1.2.3.4 IP address


  //  Some real listening shit
  rv = listen(fd, SOMAXCONN);
  if (rv)
  { die("listen()"); }


  while( isTrue == true )
  {

    struct sockaddr_in client_addr = {};
    socklen_t addrlen = sizeof(client_addr);
    int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
    if ( connfd < 0 )
    {continue;}

    do_something(connfd);
    close(connfd);

  }


  return 0;

}





