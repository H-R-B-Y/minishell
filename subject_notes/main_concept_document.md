
this is the process flow as i see it now:

## collect the current environemnt variables

at the start of the program we need to store the environment variables so that we can pass them to
 child processes that we execute.

## readline loop

The readline loop takes the user input from the command line.

the line needs to be split on (\n) if applicable and only the first line is parsed as a command at this point.

we do not need to add the line to the history record at this point because the line may be incomplete.

the text returned from readline might need to be freed (we need to track this)

the readline loop SHOULD ONLY print the prompt if the current input is a TTY not an FD:
- we need to use `isatty()` to check this.

There are singal handlers and key combinations that we need to make sure we handle:

if we are a tty:
- singal handler for SIGINT (ctrl + c):
- - if we are running a command, we send the SIGINT to the command
- - if we are waiting for a line to be read, we clear the user input and start the prompt again on a new line
- EOF handler (ctrl+D): this does not send a signal but EOF is sent through the terminal
- - if we are running a command we do not need to do anything
- - if we are not running a command we need to close the minishell program (safely!! we need to free memory and restore signal handlers)

if we are not a tty:
- singnal handler for SIGINT does not need to be set, SIGINT should kill the minishell.
- not sure what happens for EOF if we are not in interactive mode?


!!!! NOTE: there may be more signal handlers that we need like (child process terminated for `&` operations)

signal handlers need to be setup and removed correctly.
what i mean by this is:
- if the main minishell program sets up a signal handler all forks (commands that we run) will inherit this signal handler so we need a way to restore the original signal handlers for all the forks.


## tokeniser

the tokeniser splits the string into a token list, this is in place rn but may need updating down the line.

the token arrray is allocated on the heap and will need to be freed later.

after the token array is constructed we check if the tokens are valid (quotes are matched and parenthesis are matched).

if the token array is not valid:
- check if there are other lines split from the original input (see readline loop) and read them line by line until the tokens are valid

if the tokens are not valid after reading the extra lines:
- go back to readline loop to append more tokens until the token array is complete
- all lines read in addition to the first in order to complete the command need to be added to the history record.


> tokeniser is pretty much done, though there are some edge cases that might need to be tested, but the states are all there, so future state transitition only need to be applied to the mapping.

## AST

The ast will be constructed to provide a path of execution that makes sure that all commands are run in the correct order with the correct inputs and outputs.

during the tree construction the tree nodes will be allocated and will need to be free'd later. 
currently the nodes contain vectors that store the tokens that are relevant to them, sometimes this vector is allocated and will need to be free'd:
- we may need a flag to signal which vectors will need to be free'd and which vectors are just stack allocated.

the ast should be used to check for syntax errors, though the list of potential errors has not been written down (I will see if i can write an exhaustive list)
if a syntax error is found during the construction of the AST:
- construction of the AST stops here
- a line is printed to the consoles STDERR acknowledging the error
- the tree is free'd
- the tokens are free'd
- we go back to the readline loop for the next command.

> AST will be updated to include the HEREDOC setup, heredoc will be added to the redirect list.

## Execution path

we traverse down the tree's left nodes, upon reaching certain nodes we do certain things:

#### AND / OR nodes

fork, fork runs left node
wait for the fork to finish
- (OR) if left fork failed: fork again, run right node, set OR node return value to right node.
- (OR) if left fork succeeded: do not fork again, set OR node return value to the left node.
- (AND) if left fork failed: do not fork again, set AND node return value to the left node.
- (AND) if left fork succeeded: fork again, run right node, set return value to right node.

#### SEQ nodes

for `;` sequence:
fork and run left node, wait until it finishes, then fork and run right node. set return value to right node.

if there is no right node, we set return value to left node. 

for `&` sequence:
fork and run left node, then fork again and run right node.
i think we can use `wait` instead of `waitpid` to wait until either one returns, instead of waiting on one before the other,
this way we can take the return value of the one that finished last.
set return value to the node that finishes last.

if there is no right node we do not need to wait for the left node, we can go back up the tree.

!!! NOTE: it may not be needed to wait on the left node at all, it should be run in the background.

#### for SUBSHELL nodes

fork and run subshell, set return value to the return value of subshell

#### for PIPE nodes

create a pipe. 

fork 1:
- set pipe write end to the STDOUT
- run left node.

fork 2: 
- set pipe read end to the STDIN
- run right node.

return value is return value of the command that returns last (we can expect this to be the right node?)

#### for command node

fork:
- prep argv and substitute variables (see command prep)
- open redirects
- execve

parent:
- waitpid on child process
- set return value to the return value of the command.


------

that should be all the node type, if not i will update the list later.

note that the execution tree uses ALOT of forks, we need to be very careful here that we avoid fork bombing. 
we could very quickly crash if we create a fork bomb so we need to be absolutely sure that this cannot happen.


## Command prep

This step is not run straight away, and only run Just In Time, that is, when we are traversing the execution path,
we only need to prep the commands that we are going to run RIGHT NOW.

#### the first step of the command prep will be to split the tokens into redirections and parameters:
```
$ < input.txt cat > output.txt

redirect input.txt to stdin
redirect stdout to output.txt
prep the argv: (char **){"cat", NULL};
```

if files do not exist for redirection:
- inputfile doesnt exist: we print error (dont know if we are supposed to run the command in this case)
- outputfile doesnt exist: we create the output file
- inputfile doesnt have read permission: we print error (again not sure if we should run the command)
- ouputfile doesnt have write permission: we print an error ( again not sure if we need to run the command lol )

#### next we need to check that the command is actually a runnable binary:

split PATH from environment, match path+command_name until we find a file that exists and is executable:
if we do not find a file we stop cleaning up this tree node, we mark it as finished, and we set its return value to an error value.
we also print the error on STDERR.

some commands will not be binaries and we should check there before we check for binaries, these are the builtins that are mentioned in the subject:
- `echo` with option -n
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

#### variable expansion

We need to ensure that any and all variables that need to be expanded will be expanded.
We can strchr for the dollar symbol in each token that is not already marked as `tokens_expanded` and substitute the variable.
variables can come from:
- environment variables (like `PATH`)
- shell local variables (local to minishell after `MYVAR="1234"` has been executed)
- last return value (which is replaced as `$?`)

#### then we need to construct the argv
Command prep:
because the tree nodes just contain a vector of tokens, the tokens will need to be converted into argv format:
`(char **){name_of_executable, argument_1, argument_2, ...}`

TODO: should probably write a list of all things that will need to be free'd and in what order.
note that we will need to free:
- the argv
- the strings that we have substituted any variables in?

but we need to be sure that we dont free the token strings in this free step because the tokens strings do not originate here.



