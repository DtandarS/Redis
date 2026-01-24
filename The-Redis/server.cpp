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

static void msg_errno(const char *msg)
{
  fprintf(stderr, "errno[%d] %s\n", errno, msg);
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

static void fd_set_nb(int fd)
{
  errno = 0;
  int meows = fcntl(fd, F_GETFL, 0);
  if (errno)
  {
    die("fcntl error");
    return;
  }

  meows |= O_NONBLOCK;

  errno = 0;
  (void)fcntl(fd, F_SETFL, meows);
  if (errno)
  {
    die("fcntl set error");
  }
}


/* ============================ */
struct Conn
{
  int fd  = -1;
  //  Event loops intention

  bool want_read = false;
  bool want_write = false;
  bool want_close = false; 

  //  Buffer IO

  std::vector<uint8_t> incoming_juice;
  std::vector<uint8_t> outgoing_meows;

};
/* ============================ */

static void buf_append(std::vector<uint8_t> &buf, const uint8_t *data, size_t len)
{
  buf.insert(buf.end(), data, data + len);
}

static bool one_req(Conn *conn)
{
  //  This one tries to parse the protocol: message header
  if (conn->incoming_juice.size() < 4)
  {return false;}
  uint32_t len = 0;
  memcpy(&len, conn->incoming_juice.data(), 4);
  if (len > max_message)
  {
    msg("too long");
    conn->want_close = true;
    return false;
  }

  //  Parcing the message body
  if (4 + len > conn->incoming_juice.size())
  {return false;}
  const uint8_t *request = &conn->incoming_juice[4];
  printf("client says : len:%d data:%.*s\n",
      len, len < 100 ? len : 100,  request);
  buf_append(conn->outgoing_meows, (const uint8_t *)&len, 4);
  buf_append(conn->outgoing_meows, request, len);

  buf_consume(conn->incoming_juice, 4 + len);

  return true;  //  Returns true on success
}

static Conn *handle_accept(int fd)
{
  //  Client accept
  struct sockaddr_in client = {};
  socklen_t addrlen = sizeof(client);
  int connfd = accept(fd, (const struct sockaddr *)&client, &addrlen);
  if (connfd < 0)
  {
    die("accept() error");
    return NULL;
  }
  //  Set the new connection to be non-blocking
  fd_set_nb(connfd);

  //  Creating new struct for connection
  Conn *conn = new Conn();
  conn->fd = connfd;
  conn->want_read = true; //  Reads first request

  //  Returns the connections from this function
  return conn;
}

static void handle_read(Conn *conn)
{
  //  This does the non-blocking read
  uint8_t rbuf[4 * 1024];
  ssize_t rv = read(conn->fd, rbuf, sizeof(rbuf));
  if (rv < 0 && errno == EAGAIN) 
  {return;}
  //  Handles IO error
  if (rv <= 0)
  {
    msg("read() error");
    conn->want_close = true;
    return; //  Want close
  }
  //  Simple EOF handler
  if (rv == 0 )
  {
    if (conn->incoming_juice.size() == 0)
    {msg("client closed");}
    else
    {msg("Unexpected EOF");}
    conn->want_close = true;
    return;
  }
  //  Adds new data into the 'Conn::incoming_juice' buffer
  buf_append(conn->incoming_juice, rbuf, (size_t)rv);

  //  Parcing the request
  while (one_req(conn))
  {} 


  if (conn->outgoing_meows.size() == 0)
  {
    msg("ready to write");
    conn->want_read = false;
    conn->want_write = true;

    return handle_write(conn);
  }

  one_req(conn);
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



  //  Map of all the clients connections keyed by fd
  std::vector<Conn *> fd2conn;
  //  The even loop itself
  std::vector<struct pollfd> poll_args;
  while( isTrue == true )
  {
    //  Prepares the arguments for poll()
    poll_args.clear();
    struct pollfd prd = {fd, POLLIN, 0};
    poll_args.push_back(prd);
    //  The rest of the following is the socket listening
    for (Conn *conn : fd2conn)
    {
      if (!conn)
      {continue;}
      struct pollfd pfd = {conn -> fd, POLLERR, 0};
      //  poll() flags from the applications intent
      if (conn -> want_read)
      {pfd.events |= POLLIN;}
      if (conn -> want_write)
      {pfd.events |= POLLOUT;}
      poll_args.push_back(pfd);
    }


    //  Wait for any readiness signals
    int rv = poll(poll_args.data(), (nfds_t)poll_args.size(), -1);
    if (rv < 0 && errno == EINTR)
    {continue;}
    if (rv < 0)
    {
      die("poll");
    }


    //  Sockets listening protocols
    if (poll_args[0].revents)
    {
      if (Conn *conn = handle_accept(fd))
      {
        //  Puts into the map
        if (fd2conn.size() <= (size_t)conn->fd)
        {fd2conn.resize(conn->fd + 1);}
        assert(!fd2conn[conn->fd]);
        fd2conn[conn->fd] = conn;
      }
    }
    //  On this section I had trouble focusing. I have some idea on why but currently I am really annoyed by the amount of time that has passed and the amount of time I haven't code.

    //  Note that we skip the first one since it is reserved for listening. 
    for (size_t i = 1; i < poll_args.size(); ++i)
    {
      uint32_t ready = poll_args[i].revents;
      if (ready == 0)
      {continue;}

      Conn *conn = fd2conn[poll_args[i].fd];
      if (ready & POLLIN)
      {handle_read(conn);}
      if (ready & POLLOUT)
      {handle_write(conn);}

      //  Handles poll error POLLERR
      if ((ready & POLLERR) || conn-> want_close)
      {
        (void)close(conn->fd);
        fd2conn[conn->fd] = NULL;
        delete conn;
      }
    }



    close(connfd);
  }


  return 0;

}





