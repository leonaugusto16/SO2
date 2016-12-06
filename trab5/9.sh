#!/bin/bash
valor=1
for var in "$@"
do
    echo "Parâmetro $valor:$var"
    valor=$(( $valor + 1 ))
done
