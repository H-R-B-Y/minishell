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
