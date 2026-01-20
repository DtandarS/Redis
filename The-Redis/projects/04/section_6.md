# Event loops


First we created a connection structure in order to pass in non-blocking read and write. We also create a table of fds so that we can store in multiple connections in order to process the data.

``` c++
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
```

We then change up the main iteration loop to accept multiple connections and store those on a map to be processessed using poll()

poll() usually return when atleas on e of the fds is ready but ocationally errno might retunr EINTR when nothing is ready

EINTR is a handler that processes some accidental Unix signals. It is not expected in non-blocking syscall

Even if we didn't use signal. We should still handle EINTR, because it may cause unexpected signals.

accept() is treated like read() readiness notification so we use pollin. After this we check the first fd to see if we can accept().



