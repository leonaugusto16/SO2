VAR=$1
VAR2=$2

JUNDA="$(echo "$VAR2" | grep "$VAR")"
if [ -n "$JUNDA" ]; then
	echo $VAR está contido em $VAR2
fi

