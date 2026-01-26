# IP Addresses, Structs, and Data Munging
---
## Internet Address Versions
IP addresses has two versions. Version 4 and version 6, both respectively called IPv4 and IPv6.

IPv4 consist of four bytes separated with dots. The form looks something like: 192.0.32.1

IPv6 on the other hand has hexadecimal representation with each two-byte chunks being separated with colons: 2001:2e08:c9d2:aie7:83e4:953e:a5ae:2005

Essentially every website, device, computer, laptop, puppy, satellite, planet, parking meters has IPv4 and we are slowly running out of available addresses. The are now billions upon billions different devices that need some sort of identification protocol.

 The loopback address for IPv6 is always `::1`. It essentially means that we are accessing this machine we are using right damn now. The loopback address for IPv4 is 127.0.0.1 so not a real wildcard.

 With compatibility on both ends there will never be an issue of not having enough IP for the masses or even galaxies.

## Subnets

Netmask are a way to separate an internet portion and a host portion of the IP. The IPv4 has for example class A where the first one byte is reserved for the internet and the rest is reserved for the host. On the opposite end is a class C where the first 3 bytes is reserved for the internet and the last is for the host. But we now need to give out host address with an extension so others and used the same IP too.

This is mostly for organizational purposes. Subnetmasks used to something like this: 255.255.255.0. A large string of bits that represents recipients device. We soon realize that this is not good since most people doesn't have any cles, how many bits that is. Now a new way to declare host portions is to add decimal value at the end of IPs like so: 127.0.0.1/30




