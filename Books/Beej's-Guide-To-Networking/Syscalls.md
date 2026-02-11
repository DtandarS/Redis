# Syscalls

System Calls are essentially kernel functions you call to perform and access network functionalitios. These syscalls aren't really well documented in term of initialization order in man pages. 

We used to have to use gethostbyname() function in order to do DNS lookups and hand those loads in to sockadd_in structure manually. Thankfully this is no longer necessary nor is it desired due to incompatibility nature between IPv4 and IPv6. All of these can now be done with getaddrinfo() functions.

``` cpp

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(
        const char *node,       //  Node represents IP or website addressess like "www.google.com"
        const char *service,    //  Service represents port numbers or HTTP
        const struct addrinfo *hints,
        struct addrinfo **res);

```

``` cpp

int status;
struct addrinfo hints;
struct addrinfo *server_info;

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_INET;
//  You can set this with AF_INET or AF_INET6 for each respective version. or AF_UNSPEC if you don't care whether we are using IPv4 or IPv6

hints.ai_socktype = SOCK_STREAM
//  This can be set to either datagram aka SOCK_DGRAM or regular stream socket aka SOCK_STREAM


if ( (status = getaddrinfo(NULL, "25565", &hints, &server_info)) != 0 )
{

fprintf(stderr, "getaddrinfo() error [ %s\n ]", gai_strerror(status));
exit(1);

}

```





