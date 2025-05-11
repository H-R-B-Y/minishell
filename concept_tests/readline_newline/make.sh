

make --directory ../../lib/libft
cp ../../lib/libft/libft.a ./
cc -lreadline readline_newline.c libft.a -o readline_newline.out
rm libft.a
