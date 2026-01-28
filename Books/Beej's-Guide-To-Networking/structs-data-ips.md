# IP Addresses, Structs, and Data Munging

<!--toc:start-->
- [IP Addresses, Structs, and Data Munging](#ip-addresses-structs-and-data-munging)
  - [Internet Address Versions](#internet-address-versions)
  - [Subnets](#subnets)
  - [Port Number](#port-number)
  - [Byte Order](#byte-order)
  - [Internet Struct](#internet-struct)
<!--toc:end-->

---
## Internet Address Versions
IP addresses has two versions. Version 4 and version 6, both respectively called IPv4 and IPv6.

IPv4 consist of four bytes separated with dots. The form looks something like: 192.0.32.1

IPv6 on the other hand has hexadecimal representation with each two-byte chunks being separated with colons: 2001:2e08:c9d2:aie7:83e4:953e:a5ae:2005

Essentially every website, device, computer, laptop, puppy, satellite, planet, parking meters has IPv4 and we are slowly running out of available addresses. The are now billions upon billions different devices that need some sort of identification protocol.

 The loopback address for IPv6 is always `::1`. It essentially means that we are accessing this machine we are using right damn now. The loopback address for IPv4 is 127.0.0.1 so not a real wildcard.

With compatibility on both ends there will never be an issue of not having enough IP for the masses or even galaxies.

---
## Subnets

Netmask are a way to separate an internet portion and a host portion of the IP. The IPv4 has for example class A where the first one byte is reserved for the internet and the rest is reserved for the host. On the opposite end is a class C where the first 3 bytes is reserved for the internet and the last is for the host. But we now need to give out host address with an extension so others and used the same IP too.

This is mostly for organizational purposes. Subnetmasks used to something like this: 255.255.255.0. A large string of bits that represents recipients device. We soon realize that this is not good since most people doesn't have any cles, how many bits that is. Now a new way to declare host portions is to add decimal value at the end of IPs like so: 127.0.0.1/30

---
## Port Number

There is another addresses that is used by TCP(stream sockets) and coincidentally, by UDP(datagram sockets). A 16-bit number that act as host for local connections. These are called port numbers. In term of analogy we can think of IP addresses like a street in an urban city and port are the houses beside the street.

The ports are needed to differentiate two or more services in a single computer from the same IP address. Usually HTTP uses port 80. Telnet uses 23, SMTP uses port 25, the Doom game uses the port 666, so on and so forth. Ports under 1024 are usually special and requires a special OS privilege to use.

---
## Byte Order

Big-Endian is a way for your PC to store data with a big end first

Little-Endian is way for you PC to store data in reverse order

Say we want to store a two-byte hex value of b34f. Big-Endian would accomplish this by storing it in sequential byte b3 followed by 4f. Little-Endian on the other hand stores data in reverse order so 4f followed by 3b

Your computer stores Host Byte Order all in different way depending on the architecture of the processing unit.

Data structures must be filled out with two- or four-byte numbers when building the package.

You don't need to know the native Host Byte Order since you get to assume Host Byte Order is not even rightr and we'll get to run the values through a function that vonberts these value into Network Byte Orders

Say we want to convert short (e.g. two bytes) Host to Network Byte order. We will have to use htons()

```
htons()  --  Host to Network short
htonl()  --  Host to Network long
ntohs()  --  Network to Host short
ntohl()  --  Network to Host long
```

Basically we always want to convert from Host Byte Order to Network Byte Order before we sent to package out to the wild. Then on the recipient computer we want to convert Network Byte Order back to Host Byte Order.

---
## Internet Struct

The first struct we should call is addrinfo. It contains info used for socket preparation. Nothing else really. 

We can use `AF_INET` for IPv4 or `AF_INET6` for IPv6 

Technically you could just call getaddrinfo() to fill out your addrinfo structure with. To get most out of the these structures it is good to take a look underneath the hood

Sockaddr structure's `sa_family` uses either `AF_INET` or `AF_INET6` in our use cases but it can be really anything. `sa_data` hold destination address and port number for the socket. But this is unyielding since we have to pack the addresses all by ourself. Not very efficient

To deal with this, programmers have developed `sockaddr_in`. "in" stands for "internet". This is mainly for IPv4 usage. For IPv6 similar is also implemented called `sockaddr_in6`. `sockadder_in`'s first elemenet `sin_family` corresponds to sockaddr's `sa_family` and should be set to `AF_INET`. `Sin_zero` should be set to zeros with `memset()`. Finally `sin_port` should be or more like must be set to Network Byte Order aka `htons()`

And at last we havbe sockaddr_storage that's designed to be large enough storage to hold both IPv4 and IPv6 address. We pass to this parallel structure if for example we fill out sockaddr. We can check the ss_family for the IPv4 or IPv6 then cast it to their respective structures.




