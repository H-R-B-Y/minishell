#!/usr/bin/env bash


true  && echo OK
echo $?
false && echo BAD
echo $?
false || echo RECOVER
echo $?
true  || echo SKIP
echo $?
false && true || echo FALLBACK
echo $?


echo "First test"               # 1
echo $_                         # 2: should print "test"
echo "Second" "value"           # 3
echo $_                         # 4: should print "value"
var="hello world"               # 5
echo $_                         # 6: should still print "value" (var assignments don't update $_)
ls /tmp > /dev/null             # 7
echo $_                         # 8: should print "/tmp"
echo "Final check"              # 9
echo "Result of \$_ is: $_"     # 10
(true; echo semicolon)           # 11
echo $_                          # 12: should print "semicolon"

false && echo success            # 13: echo doesn't run
echo $_                          # 14: still "false", since `false` was last to run

true || echo fail                # 15: echo doesn't run
echo $_                          # 16: should print "true"

echo "pipe test" | cat           # 17
echo $_                          # 18: should print "cat" in Bash


echo "First test"
echo $_               
echo "Second" "value"           
echo $_                  
var="hello world"             
echo $_                       
ls /tmp > /dev/null             
echo $_                         
echo "Final check"              
echo "Result of \$_ is: $_"   
(true; echo semicolon)          
echo $_                       

false && echo success            
echo $_                         

true || echo fail              
echo $_      

echo "pipe test" | cat          
echo $_                 


#new line management
echo vamos ;
env | 

grep HOME ; echo "
$?"

echo vamos ;
env | 

grep HOME ; echo 
"
$?"

echo
echo vamos
echo $?
lunacos costo
echo $?
testdir
echo $?
./testdir
echo $?
mkdir testdir
echo $?
testdir
echo $?
./testdir
echo $?
ls -l | wc
echo $?


<< eof
vamos
luna
eso
eof


grep nomatch /dev/null | cat && echo PIPE
echo $?

(cd /; false) || echo PARENT
echo $?



cquinter@DESKTOP-7CUJOKT:~/42london/common_core/l3/minishell$ vv$lvara2mo\$\s=\$1a23
vv$s=$1a23: command not found
cquinter@DESKTOP-7CUJOKT:~/42london/common_core/l3/minishell$ vv$'vara2mo\$\s=\$1a2'3
vvvara2mo\$\s=\$1a23: command not found
cquinter@DESKTOP-7CUJOKT:~/42london/common_core/l3/minishell$ vv$vara2mo$vars=\$1a23
vv=$1a23: command not found
cquinter@DESKTOP-7CUJOKT:~/42london/common_core/l3/minishell$ vv$vara2mo$var=\$1a23
vvLOCOOO=$1a23: command not found
cquinter@DESKTOP-7CUJOKT:~/42london/common_core/l3/minishell$ vv$'vara2mo$v\nars=\$1a2'3
vvvara2mo$v
ars=\$1a23: command not found