

## signal recieving

the main process will usually be waiting on something, either reading a line
or waiting on a pid.

when waiting on something and a signal is recieved (i will assume) the wait 
is interrupted, it is at this point we can check the global variable to see 
what the interuption was caused by and in turn perform some kind of action:
i.e. kill child process, discard the readline and redisplay the prompt?

I am assuming that that is how it works?


## forks will be a problem

when setting up signal handlers in the main thread. whenever we fork to run a command we will need to restore the
signal handlers to how they were before minishell changed them in the child process, otherwise child processes will ignore signals we send it.