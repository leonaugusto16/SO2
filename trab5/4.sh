VAR=$1
i=$VAR

while [ $VAR -gt -1 ]
do
	printf "%d " $VAR
	let VAR=VAR-1
done 
echo
