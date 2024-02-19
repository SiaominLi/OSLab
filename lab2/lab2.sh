
l=1
g=10

echo enter the target number between $l and $g
read target

guessnum(){
	echo enter the target number:
	read num
	
	while [ $num -ne $target ];do

		if test $target -lt $num; then
			g=$num
			
		fi
		if test $target -gt $num; then
			l=$num
		fi

		echo "please enter a number between $l and $g:"
	 	echo enter the target number:
		read num
	done
	echo Bingo!
}
guessnum;
