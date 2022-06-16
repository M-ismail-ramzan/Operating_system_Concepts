#! /bin/bash

# Just a check COndition
if [[ $# -lt 2 ]] || [[ $# -gt 2 ]]
then
    echo " Argument Must be 2 "
    exit
fi
#calculating mid point for the full inverted graph
midpoint=$((($2/2)+1))
counter=0
# For the outside loop
for run in $(seq $2);
do
    #For the inside loop
    for run2 in $(seq $2);
    do
        # condition to draw a left graph
        if [[ run -ge run2 ]] && [[ $1 == "left" ]] ;
        then
            echo -n " * "
        fi
        
        # COndition to draw a right grapg
        if [[ run2 -ge $((6-$run)) ]] && [[ $1 == "right" ]] ;
        then
            echo -n "*"
        else
            echo -n " "
        fi
        
        # Condition to draw a full inverted graph
        if [[ run2 -le $(($midpoint-$run)) ]] || [[ run2 -ge $(($midpoint+$run))  ]] && [[ $1 == "inverted_full" ]] ;
        then
            echo -n "*"
        else
            echo -n " "
        fi
    done
    # Creating the Full Grap
    if [[ $1 == "inverted_full" ]] && [[ $counter -le $midpoint ]]
    then
        echo -e " "
        counter=$(($counter+1))
    fi
    
    if [[ $1 == "right" ]] || [[ $1 == "left" ]]
    then
        echo -e "\n"
    fi
done