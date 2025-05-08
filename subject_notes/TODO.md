
# To Do (global)

---
### Document AST and Tokeniser
assigned to: harvey

Alot of code doesnt have documentation, or has outdated documentation.

---

---
### Figure out TTY vs non-TTY execution?
assigned to: 

There are a few things that need to change when we are not running code in a TTY,
one thing is the signal handlers, SIGINT needs to kill the parent process if not 
in a TTY. 

There should be a list of things that we need to account for when not running in a TTY.

---

---
### Signal handling
assigned to: 

Signal handlers need to be setup to handle SIGINT and whatever is sent with `ctrl + \` (SIGTERM or SIGSEGV????).

we should also be able to handle SIGCHLD in some way as we will be running programs in the background, but this is optional as subject doesnt specify we need to handle `&` tokens.

---

---
### Token escaping needs to be checked (optional)
assigned to: 

Token escaping (use of "\") is somewhat handled but needs to be double checked.

This might require changes to the tokeniser, and will need to be accounted for when 
constructing commands.

---

---
### Token validation and errors
assigned to: 

There is a list of token errors `e_tokerr` that is not complete.

There are missing errors and no code yet written to find these errors in the validation stage, 
Some examples of errors that are not accounted for are: (list is not complete)
- `~$ &&` and that doesnt have a valid left token
- `~$ ||` or that doesnt have a valid left token
- `~$ &` disown that doesnt have a valid left token
- `~$ |` pipe that doesnt have a valid left token

Some of these errors may be easier to catch in the AST construction?

I think we can categories these errors as fixable and unfixable:
- `cat &&` is a fixable error as we can continue reading lines until the right token is complete
- `&&` is unfixable because we cannot preppend lines before the and token

---

---
### Redirection and HEREDOC handling
assigned to: 

At some point after token validation and before AST execution we need to setup the redirection,

redirection is not a part of the AST but part of the command token sequence, meaning that the
command nodes will have to be checked for the redirection tokens.

we can either open the files themselves at this stage allowing us to print any errors before anything is executed or we can do it on the fly later? 

for heredoc we will need to open the file at this stage because we need to write the lines read
from the stdin into a temp file.

---

---
### AST execution
assigned to: 

After constructing a valid AST we need to execute the tree,
we traverse the tree from top down the left nodes and then down the right nodes.

certain nodes will need to be run in parallel depending on the parent nodes.

---

---
### Command prep
assigned to: 

When traversing the ast, when we encounter a command node that needs to be executed we first need to prepare the command, this will mean finding the path of the executable, splitting the arguments, expanding arguments, removing escape characters (\\), doing any fd duping required by the redirections.

the end result of the prep should be that the current thread/fork/process is setup for execve and the argv is ready (i.e. has the command path and all arguments)

---

---
### Cleanup
assigned to: 

Probably going to be a big job, but we need to be able to cleanup the multiple different
stages of the program independantly, the tree needs to be free'd, the tokens need to be free'd, any signal handlers need to be cleaned up?, all open file descriptors need to be closed.

we should be able to run these steps independantly.

---

---
# Done (global)




---
# template

```
---
### TITLE
assigned to: 

description...

---
```
