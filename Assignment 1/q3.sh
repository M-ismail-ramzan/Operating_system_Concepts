#! /bin/bash
#checking that the argument must be one
if [[ "$#" -eq 1 ]]
then
    #creating the directory
    mkdir safe_rm_recycle 2>/dev/null
    #Move the files to this directory
    cp $1 safe_rm_recycle
    # remove the file
    rm $1
else
    echo "Error: Argument Must be One "
fi