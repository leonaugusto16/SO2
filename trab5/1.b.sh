#!/bin/bash    

echo Horas:
uptime | cut -d" " -f 2

echo 
echo Ocupação Disco:
df -h

echo
echo Usuários Logados:
who | grep tty | cut -d" " -f 1
