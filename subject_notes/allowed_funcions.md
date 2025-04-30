## readline
```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
```
There is alot to unpack in this function but it can be distilled to this:

readline will read a line from the terminal and return it, using prompt as a prompt. If prompt is NULL or the empty string, no prompt is issued.  The line returned is allocated with malloc(3); the caller must free it when finished. The line returned has the final newline removed, so only the text of the line remains.

## rl_clear_history
`#include <.h>`

cannot find manual page for this

## rl_on_new_line
`#include <.h>`

cannot find manual page for this

## rl_replace_line
`#include <.h>`

cannot find manual page for this

## rl_redisplay
`#include <.h>`

cannot find manual page for this

## add_history
`#include <.h>`

Place string at the end of the history list. The associated data field (if any) is set to NULL. 

## printf
`#include <stdio.h>`

do not need explination.

## malloc
`#include <stdlib.h>`

do not need explination.

## free
`#include <stdlib.h>`

do not need explination.

## write
`#include <unistd.h>`

do not need explination

## access
`#include <unistd.h>`

Checks if a fd is accessible, can also be used to check the access permissions of a file, or if the file exists.

## open
`#include <fcntl.h>`

open creates a connction between a file and a file descriptor.

## read
`#include <unistd.h>`

Read n bytes from a file descriptor.

## close
`#include <unistd.h>`

deallocate a file descriptor.

## fork
`#include <unistd.h>`

fork the current process (parent process returns child process id)

## wait
`#include <sys/wait.h>`

wait indefinitly until a child process is terminated.

## waitpid
`#include <sys/wait.h>`

wait for the process pointed too by pid is terminated.

## wait3
`#include <sys/wait.h>`
The wait3() and wait4() system calls are similar to waitpid(2), but additionally return resource usage information about the child in the structure pointed to by rusage. 

## wait4
`#include <sys/wait.h>`
The wait3() and wait4() system calls are similar to waitpid(2), but additionally return resource usage information about the child in the structure pointed to by rusage. 

## signal
`#include <signal.h>`

Need to look into this a bit more, it appears to be able to set a function to run when 

## sigaction
`#include <signal.h>`

binds an action to a signal, action can be created from empty set, and populated as needed. see man page on how to setup handlers.

## sigemptyset
`#include <signal.h>`

populates a signal handler struct to be empty (initialisation).

## sigaddset
`#include <signal.h>`

add signal to set ??? not sure what this is for.

## kill
`#include <signal.h>`

send a signal to a process by pid.

## exit
`#include <stdlib.h>`

clean exit.

## getcwd
`#include <unistd.h>`

gets the absolute pathname of the current working directory.

requires a buff to write the pathname too, and the size of said buffer.

## chdir
`#include <unistd.h>`

changes the current working directory to be the path pointed too by argument.

## stat
`#include <sys/stat.h>`

stat can be used to get information about a file at the location of the path argument. 

difference between stat and fstat: 

fstat is used on open file descriptors.

## lstat
`#include <sys/stat.h>`

returns informaiton about symbolic link instead of the file it points too.

## fstat
`#include <sys/stath>`

get information about a file from an open file descriptor. 

## unlink
`#include <unistd.h>`

removes a link to a file, if path is a symbolic link the link is destoryed.

else it will remove the link to the file (if this is the only link to the file (i.e. just the file) then the file is counted as deleted though the inode will likely still exist for some time).

## execve
`#include <unistd.h>`

execute a command with arguments and with specified environment variables.

## dup
`#include <unistd.h>`

duplicate a file descritpr, returns a new file descriptor duplicated from the arg. 

## dup2
`#include <unistd.h>`

dup 2 duplicates the file descritor in its first arg, to the file descriptor in its second arg. 

## pipe
`#include <unistd.h>`

opens a new pipe, index 0 is read end of the pipe index 1 is the write end of the pipe.

## opendir
`#include <dirent.h>`

open dir opens a new directory stream for the directory descibed by arg. the stream is pointed at the first entry in the directory.

## readdir
`#include <dirent.h>`

returns a pointer to a directory entry struct representing the next entry in the directory stream.


## closedir
`#include <dirent.h>`

closes a directory stream. 

## strerror
`#include <string.h>`

returns a pointer to a string that describes the error code passed in the args.

## perror
`#include <errno.h>`

prints a message to stderr describing the last error encountered during a call to a system or library function.

## isatty
`#include <unistdq.h>`

tests whether an fd is referring to a terminal?

## ttyname
`#include <unistd.h>`

returns a pointer to the null-terminated pathname of the terminal device that is open of the file descriptor fd.

the return value may point to static data that may be overwritten by the next call.

## ttyslot
`#include <unistd.h>`

returns the index of the current users entry in some file.

has a lot of info about what this actually means inside the man page, but we can view this as getting the slot of the tty i.e. 8 for /dev/tty8

## ioctl
`#include <sys/ioctl.h>`

send control commands to an io stream, what this means and what it will/might be used for in this project is an absolute myth to me. 

## getenv
`#include <stdlib.h>`

lookup a key in the path and return its value. 

## These all look strange and i dont know what they are used for:

## tcsetattr
`#include <unistd.h>`


## tcgetattr
`#include <unistd.h>`

## tgetent
`#include <term.h>`

## tgetflag
`#include <term.h>`

## tgetnum
`#include <term.h>`

## tgetstr
`#include <term.h>`

## tgoto
`#include <term.h>`

## tputs
`#include <term.h>`


