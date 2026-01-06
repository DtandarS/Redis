

#include <master.h>



static void die(const char *msg)
{
  int err = errno;
  printf("[%d] %c\n", err, *msg);
  abort();
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



