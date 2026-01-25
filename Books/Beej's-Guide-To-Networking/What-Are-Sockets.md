# The Beginning of the End.

## 1. What Are the Sockets

Sockets are Unix file descriptors. Just about everything in Unix systems are files whether that is a network connection, a terminal, a pipe, or on-the-disk files, and etc. If we want any form of communication over networks then we need the file descriptor. More specifically a socket descriptor

When using sockets it is preferred to use `send()` and `recv()` for overall greater control.

Two main internet sockets types that we should know are stream sockets and datagram sockets. Stream sockets are the primarily one we gonna use for its reliability and is mainly error-free. Datagram is little less reliable in a sense that the packages that are transferred could come in out of order. It's like FedEx against UPS. Both has their own strength and weaknesses.

```
Stream sockets uses TCP(Transmission Control Protocol)
```


```
Datagram sockets uses UDP(User Datagram Protocol)
```

UDP and datagram are considered as connectionless sockets. In a simple term it is just a fire and forget protocol. To get the most reliable `SOCK_DGRAM` outcome is to implement a simple ACK. In short it is just a simple answer protocol. The package recipient simply sends back a signal that it obtained the package before the server fires another load of packages. Many games, audios, and videos uses this protocol.


Data layering is waht it sounds like. The data is wrapped between protocol layers of user, protocols, ip then over physical hardware like ethernet. Luckily the only thing we have to do is to `send()` or `sendto()` the packages to destination depending on the protocol we are using.

There is really nothing that important to talk about IP routing. The kernel does all of that for you.


