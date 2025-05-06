

## signal recieving

the main process will usually be waiting on something, either reading a line
or waiting on a pid.

when waiting on something and a signal is recieved (i will assume) the wait 
is interrupted, it is at this point we can check the global variable to see 
what the interuption was caused by and in turn perform some kind of action:
i.e. kill child process, discard the readline and redisplay the prompt?

I am assuming that that is how it works?