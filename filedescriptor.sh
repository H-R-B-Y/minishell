# Test for trying to open a file that doesn't have permission
BASH="/usr/bin/bash"
MINISHELL=`realpath $1`

NOWRITE="./cannot_write"
touch $NOWRITE
chmod -w $NOWRITE

NOREAD="./cannot_read"
touch $NOREAD
chmod -r $NOREAD

echo "Test one: writing to file no write perms"

