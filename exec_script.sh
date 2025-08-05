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
###############################################################################
# builtin_tests.sh — verifies output *and* exit-status of cd, pwd, echo,
#                    export, unset and env.

pass() { printf "[\e[32mPASS\e[0m] %s\n" "$*"; }
fail() { printf "[\e[31mFAIL\e[0m] %s  (got: %s, rc=%s)\n" "$1" "$2" "$3"; }

# check "<description>" "<expected stdout>" "<expected rc>" command...
check() {
    desc=$1 want_out=$2 want_rc=$3; shift 3
    out=$("$@" 2>&1); rc=$?
    if [[ "$out" == "$want_out" && "$rc" == "$want_rc" ]]; then
        pass "$desc"
    else
        fail "$desc" "$out" "$rc"
    fi
}

###############################################################################
# 1. cd
###############################################################################
OLD=$PWD
check "cd success"            "" 0 cd /
check "cd error path"         * 1 cd /does/not/exist          # stderr pattern
cd "$OLD"   # restore for later tests

# OLDPWD toggle (dash should print previous dir)
prev=$(pwd); cd / >/dev/null
check "cd - outputs prev pwd" "$prev" 0 cd - >/dev/null

###############################################################################
# 2. pwd
###############################################################################
here=$(pwd)
check "pwd prints cwd"        "$here" 0 pwd

###############################################################################
# 3. echo
###############################################################################
check "echo text"             "hello world" 0 echo "hello world"
check "echo -n option"        "nonl" 0 echo -n "nonl"

###############################################################################
# 4. export
###############################################################################
check "export add var"        "" 0 export TESTVAR=42
check "export shows var"      "TESTVAR=42" 0 env | grep -E '^TESTVAR=42$'
check "export bad name"       * 1 export 1BAD=oops             # stderr pattern

###############################################################################
# 5. unset
###############################################################################
check "unset existing"        "" 0 unset TESTVAR
check "unset non-existent"    "" 0 unset NOT_SET
check "unset bad name"        * 1 unset 1BAD                   # stderr pattern

###############################################################################
# 6. env
###############################################################################
check "env prints PATH"       * 0 env | grep -E '^PATH='
check "env -i drops PATH"     "" 127 env -i sh -c 'exit 127'   # exit of sub-command
check "env bad option"        * 1 env -Z                       # unknown opt

###############################################################################
echo "----------- finished -----------"
