# Section 05 


The section has nothing about actual coding. In the current chapter we went over a little on blocking and non-blocking read and write request and it's function.

#### Multithreading

The multithreading is something we need if we want to process multiple request at once. Although current apps uses event loops rather than multithreading. It is still something worth looking into.

Since most of the connections are request-response pair oriented. The client could hold the connection for as long as it wants leading the server side unable to process or take int other connections.

But like I said. We will not use multithreading but rather we will use event loops. In Linux kernel. TCP stack handles incoming data in per-socket kernel side buffer transparently. `read()` simply copies from the kernel side bugger, and when the buffer is empty `read()` is then suspends the threads until next wave of data to process.

Likewise the `write()` simply copies into the kernel side buffer until the buffer is full. `write()` will only suspends when there is no more room in the buffer and stop until data is processed and it can put more data into buffer.

#### Event Loop Operation

Even loop operation requires 3 protocols.

- 1. Readiness notification: 
read buffer is not empty and write buffer is not full
- 2. Non-blocking Read: 
Read buffer is processed but is not empty all the way.
- 3. Non-blocking Write:
Write buffer has space available for data

With all of these 3 protocols combined each loop iteration waits for readiness then processes and reacts to all data without blocking the next one.

Both read and write kernel buffer needs to process and return the data immediately for the next to be processed. Both of these non-blocking function can be called repeatedly in order to empty & fill out read and write without interruption.


