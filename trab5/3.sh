VARIAVEL=$1
VARIAVEL2=$2

if test "$VARIAVEL" -gt "$VARIAVEL2"
then
echo "$VARIAVEL" "é maior que" "$VARIAVEL2"
else
echo "$VARIAVEL" "é menor que" "$VARIAVEL2"
fi
