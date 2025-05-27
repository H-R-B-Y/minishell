
when working with environment variables: 

export makes a variable part of the environment, 

when using
```
VAR=123
```
this checks to see if the VAR is in the environment, if it is then it will change
the version in the environment, if it does not exist in the environment then it
becomes part of the shell local variables.

likewise

if you set a variable locally:
```
NEWVAR=123
```
and then export it later
```
export NEWVAR
```
then it is removed from the shell local scope and added to the envp scope


also:
unset works on both shell local and environment variables
