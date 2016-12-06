#!/bin/bash    

echo "Aceita rodar o script? [y|n]"
read -r b
if [ "$b" == 'y' ] ; then
	
	echo Horas:
	uptime | cut -d" " -f 2

	echo 
	echo Ocupação Disco:
	df -h

	echo
	echo Usuários Logados:
	who | grep tty | cut -d" " -f 1
fi

