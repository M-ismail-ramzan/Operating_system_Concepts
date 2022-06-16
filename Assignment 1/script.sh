#! /bin/bash

#Simple script to print the argument send to it
echo "Argument sends are "
for arguments in $@
do
    echo "$arguments"
done;
#Seeing the Envirnmental variables from the Execve
echo "Printing Env Variables"
echo $PATH
echo $USER
echo $TERM
echo $OS2022