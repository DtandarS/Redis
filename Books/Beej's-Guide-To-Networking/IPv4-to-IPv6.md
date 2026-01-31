# Jumping from IPv4 to IPv6
---

There are some actions we need to take when we want to convert from IPv4 to IPv6. Due to this guides concern many of this are just what is talked about in the guide. There are a lot more into this.

1. Try to use getaddrinfo() to keep IP versoin-agnostic. This will help to eliminate many subsequent steps. 

2. Anything that feels like it is hard codes should be wrap in a helper functions.

3. Change AF_INET to AF_INET6 or PF_INET to PF_INET6

4. Change INADDR_ANY assignments to IN6ADDR_ANY assigments

5. Use struct sockaddr_in6 instead of regular sockaddr_in. Make sure to add the "6" to the end. 

6. Use in6_addr instead of in_addr making sure to add "6"

7. Instead of inet_aton() or inet_addr(), use inet_pton()

8. Instead of using inet_ntoa(), use inet_ntop()

9. Instead of gethostbyname(), use the superior getaddrinfo()

10. Instead of gethostbyaddr(), use the superior  getnameinfo() (although get hostbyaddr() also works with IPv6)

11. INADDR_BROADCAST will not work so use the IPv6 multicast instead.


