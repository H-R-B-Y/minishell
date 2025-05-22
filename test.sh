# testing something interesting

# escape sequence starts: 
# \033		is ESC start escape sequence

# followed by
# [			to start control sequence

# followed by
# 30–37 	Set foreground color 	
# 38 		Set foreground color 	Next arguments are 5;n or 2;r;g;b
# 40–47 	Set background color 	
# 48 		Set background color 	Next arguments are 5;n or 2;r;g;b
# 11–19 	Alternative font 	Select alternative font n − 10

printf "foreground colours\n"
printf "\033[30m test1\n"
printf "\033[31m test2\n"
printf "\033[32m test3\n"
printf "\033[33m test4\n"
printf "\033[34m test5\n"
printf "\033[35m test6\n"
printf "\033[36m test7\n"
printf "\033[37m test8\n"

printf "\033[0mforeground colour from rgb value\n"
	#e7d1ff 	
printf "\033[38;2;231;209;255m test \n"
	#e1c4ff 	
printf "\033[38;2;225;196;255m test \n"
	#d8b9ff 	
printf "\033[38;2;216;185;255m test \n"
	#d2afff 	
printf "\033[38;2;210;175;255m test \n"

printf "alternate fonts ??\n"
printf "\033[10m test1\n"
printf "\033[11m test1\n"
printf "\033[12m test2\n"
printf "\033[13m test3\n"
printf "\033[14m test4\n"
printf "\033[15m test5\n"
printf "\033[16m test6\n"
printf "\033[17m test7\n"
printf "\033[18m test8\n"
printf "\033[19m test9\n"