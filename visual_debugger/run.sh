#! /usr/bin/bash

pipe=`mktemp -u`
mkfifo $pipe
p=`pwd`
cd ..
make re debug=1
cd $p
source venv/bin/activate
python main.py < "$pipe" 2>&1 >/dev/null &
exec ../minishell 3> "$pipe"

