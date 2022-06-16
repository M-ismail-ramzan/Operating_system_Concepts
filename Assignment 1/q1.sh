#! /bin/bash

# i intentionaly have n't put the check for negative values

# Taking the First input from the user
echo "-----------------------------"
echo "Input First Number: "
read first_num
#Input validation
while [[ 1 ]]
do
    if [[ first_num -le 0 ]]
    then
        echo "Input First Number: "
        read first_num
    else
        break
    fi
    
done


#let's get it's last digit
first_num=$(($first_num % 10))
echo "Last Digit is $first_num"
echo "-----------------------------"
# Taking the Second input from the user
echo "Input Second Number: "
read second_num

#Input validation
while [[ 1 ]]
do
    if [[ second_num -le 0 ]]
    then
        echo "Input Second Number: "
        read second_num
    else
        break
    fi
    
done
#let's get it's last digit
second_num=$(($second_num % 10))
echo "Last Digit is $second_num"
echo "-----------------------------"
# Taking the Third input from the user
echo "Input THird Number: "
read third_num

#Input validation
while [[ 1 ]]
do
    if [[ third_num -le 0 ]]
    then
        echo "Input third Number: "
        read third_num
    else
        break
    fi
    
done
#let's get it's last digit
third_num=$(($third_num % 10))
echo "Last Digit is $third_num"
echo "-----------------------------"
# Checking for right most digit
echo -e "[+] Comparing \\nLast Digits are $first_num , $second_num , $third_num "
echo " ----------------------------------------"
# testing if 1==2 or 2==3 or 3==1
if [[ $first_num -eq $second_num ]] || [[ $second_num -eq $third_num ]] || [[ $first_num -eq $third_num ]]
then
    # true if same
    echo "[+] True"
else
    #false if not
    echo "[-] False"
fi