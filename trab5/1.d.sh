#!/bin/bash    

# Verificação se o usuário quer realmente rodar o script, caso não o programa morre sem executar nada
echo "Aceita rodar o script? [y|n]"
read -r b
# Comparação da string sem verificação de erro
if [ "$b" == 'y' ] ; then
	# Hora do Sistema
	echo Horas:
	uptime | cut -d" " -f 2
	
	# Ocupação Disco
	echo 
	echo Ocupação Disco:
	df -h
	
	# Usuários que estão logados com tty no sistema
	echo
	echo Usuários Logados:
	who | grep tty | cut -d" " -f 1
fi

