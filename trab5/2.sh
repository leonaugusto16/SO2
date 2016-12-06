#!/bin/bash   

echo Digite o nome do arquivo:
read -r name


user="$(whoami)"
output="$(find . -name $name -user "${user}")"

if [ -z "$output" ]; then
	echo "Arquivo ou Diretório não encontrado"
else
	echo "Tipo do Arquivo:"
	file $name

fi


