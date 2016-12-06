#!/bin/bash

for var in "$@"
do
	echo $var | tr -d '[:space:]'
done
echo
