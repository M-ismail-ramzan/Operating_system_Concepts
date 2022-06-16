#! /bin/bash

#NEver mind i just wrote alot big function. THere must be alternative :(
my_permissions_manager(){
    
    case $1 in
        0)
            echo " Changing PErmission to Read Write and Execute "
            # Changing the permisson for the user.
            if [[ "$2" == "u" ]];
            then
                echo " I need to change for user "
                chmod u+rwx $3
                
            fi
            
            # Changing the permisson for the group.
            if [[ "$2" == "g" ]];
            then
                echo " I need to change for group "
                chmod g+rwx $3
            fi
            
            # Changing the permisson for the owner.
            if [[ "$2" == "o" ]];
            then
                echo " I need to change for other "
                chmod o+rwx $3
            fi
        ;;
        1)
            echo " Changing PErmission to Read Write "
            # Changing the permisson for the user.
            if [[ "$2" == "u" ]];
            then
                echo " I need to change for user "
                chmod u+rw $3
                chmod u-x $3
            fi
            
            # Changing the permisson for the group.
            if [[ "$2" == "g" ]];
            then
                echo " I need to change for group "
                chmod g+rw $3
                chmod g-x $3
            fi
            
            # Changing the permisson for the owner.
            if [[ "$2" == "o" ]];
            then
                echo " I need to change for other "
                chmod o+rw $3
                chmod o-x $3
            fi
        ;;
        2)
            echo " Changing PErmission to Execute Read "
            # Changing the permisson for the user.
            if [[ "$2" == "u" ]];
            then
                echo " I need to change for user "
                chmod u+xr $3
                chmod u-w $3
            fi
            
            # Changing the permisson for the group.
            if [[ "$2" == "g" ]];
            then
                echo " I need to change for group "
                chmod g+xr $3
                chmod g-w $3
            fi
            
            # Changing the permisson for the owner.
            if [[ "$2" == "o" ]];
            then
                echo " I need to change for other "
                chmod o+xr $3
                chmod o-w $3
            fi
        ;;
        3)
            echo " Changing PErmission to Read "
            # Changing the permisson for the user.
            if [[ "$2" == "u" ]];
            then
                echo " I need to change for user "
                chmod u+r $3
                chmod u-wx $3
            fi
            
            # Changing the permisson for the group.
            if [[ "$2" == "g" ]];
            then
                echo " I need to change for group "
                chmod g+r $3
                chmod g-wx $3
            fi
            
            # Changing the permisson for the owner.
            if [[ "$2" == "o" ]];
            then
                echo " I need to change for other "
                chmod  o+r $3
                chmod o-wx $3
            fi
        ;;
        4)
            echo " Changing PErmission to Write and Execute "
            # Changing the permisson for the user.
            if [[ "$2" == "u" ]];
            then
                echo " I need to change for user "
                chmod u-r $3
                chmod u+wx $3
            fi
            
            # Changing the permisson for the group.
            if [[ "$2" == "g" ]];
            then
                echo " I need to change for group "
                chmod g-r $3
                chmod g+wx $3
            fi
            
            # Changing the permisson for the owner.
            if [[ "$2" == "o" ]];
            then
                echo " I need to change for other "
                chmod o-r $3
                chmod o+wx $3
            fi
        ;;
        5)
            echo " Changing PErmission to Write"
            # Changing the permisson for the user.
            if [[ "$2" == "u" ]];
            then
                echo " I need to change for user "
                chmod u-xr $3
                chmod u+w $3
            fi
            
            # Changing the permisson for the group.
            if [[ "$2" == "g" ]];
            then
                echo " I need to change for group "
                chmod g-xr $3
                chmod g+w $3
            fi
            
            # Changing the permisson for the owner.
            if [[ "$2" == "o" ]];
            then
                echo " I need to change for other "
                chmod o-xr $3
                chmod o+w $3
            fi
        ;;
        6)
            echo " Changing PErmission to Execute "
            # Changing the permisson for the user.
            if [[ "$2" == "u" ]];
            then
                echo " I need to change for user "
                chmod u+x $3
                chmod u-rw $3
                
            fi
            
            # Changing the permisson for the group.
            if [[ "$2" == "g" ]];
            then
                echo " I need to change for group "
                chmod g+x $3
                chmod g-rw $3
            fi
            
            # Changing the permisson for the owner.
            if [[ "$2" == "o" ]];
            then
                echo " I need to change for other "
                chmod o+x $3
                chmod o-rw $3
            fi
        ;;
        7)
            echo " Changing PErmission to Nil "
            # Changing the permisson for the user.
            if [[ "$2" == "u" ]];
            then
                echo " I need to change for user "
                chmod u-rwx $3
            fi
            
            # Changing the permisson for the group.
            if [[ "$2" == "g" ]];
            then
                echo " I need to change for group "
                chmod g-rwx $3
            fi
            
            # Changing the permisson for the owner.
            if [[ "$2" == "o" ]];
            then
                echo " I need to change for other "
                chmod o-rwx $3
            fi
        ;;
        *)
            echo "Unable to determine the permissions"
        ;;
    esac
}

while [[ 1 ]]
do

echo -e "\n1) Enter the Filename Whose Permission You want to Invert\n"
echo -e "2) Input filename and string to seach for inside \n"
echo -e "3) Even and Odd numbered Files into dummy.txt \n"
echo -e "4) Enter the Filename and Change Modified Change..\n"
echo -e "5) Exit\n"
#taking the user input
echo "Please Select the option from the menu:"
read option
#cheching what option user has selected
case $option in
    1)
        echo -e "You selected option 1\nPlease Enter the Filename with extention: "
        read file_name
        echo "Permissions are "
        # awk is a command where we speicfy the delimier and can fetch the data acordingly
        perm=`ls -l $file_name | awk '{print $1}'`
        echo $perm
        echo "Changing the Permissions"
        #Getting the permissions in numeric
        num_perm=`stat -c "%a , %n " $file_name  | awk '{print $1}'`;
        
        user_num_perm=`echo "${num_perm:0:1}"`
        group_num_perm=`echo "${num_perm:1:1}"`
        other_num_perm=`echo "${num_perm:2:2}"`
        # Now i got the permisson number
        echo $user_num_perm
        echo $group_num_perm
        echo $other_num_perm
        
        
        # this function will be responsible for changing the persmissons of user and group and others
        my_permissions_manager $user_num_perm 'u' $file_name
        
        # Sometimes when permissions are --- then we get null in the variable
        if [[ "$group_num_perm" != " " ]];
        then
            # go and change the group permissions
            my_permissions_manager $group_num_perm 'g' $file_name
        else
            chmod g+rwx $file_name
        fi
        # Sometimes when permissions are --- then we get null in the variable
        if [[ "$other_num_perm" != " " ]];
        then
            # go and change the other permissions
            my_permissions_manager $other_num_perm 'o' $file_name
        else
            chmod o+rwx $file_name
        fi
        # showing the updated permissions
        echo "Update Permissions are"
        perm=`ls -l $file_name | awk '{print $1}'`
        echo $perm
    ;;
    2 )
        echo "Please enter filename: "
        read file_name
        
        echo "Please enter the string to search for "
        read search_it
        # we don't need to code anything. Grep command does the job :)
        grep -in "$search_it" "$file_name"
        
        
    ;;
    3 )
        echo "Plase enter the value of N: "
        read n_val
        : '
        Failed approces

        #grep_out=2;dir=`ls`;for data in $dir;do echo $data| grep $grep_out;grep_out=$(($grep_out+2));echo "grep out : $grep_out";done;
        #This can be done using awk command too but lets have some fun the loops
        while read line;
        do
            # if num%2=0 // it means its even
            if [[ counter%2 -eq 0 ]]
            then
                # write the data to dummy
                #echo $line >> dummy.txt
            fi
            counter=$counter+1
        done < dummy.txt


        #here we start the coding
        dir=`ls`;
        #THis loop will run as number of files
        for files in $dir;
        do
            #ONce we got files. Lets open them one by one
            #cat $files
            # create a loop to read all the lines
            counter=1
            #read the data
            data=`head -n5 $files`;
            #now put the data at even location in the dummy.txt
            for info in $data
            do
                echo $info

            done;

            # We need to save this content at the even location
            echo $files;
        done
        '
        
        #ALright so the task was to get the even & odd numbered files not the even & odd content :(
        #LEt's do it
        rm dummy.txt 2>/dev/null
        #Get the even Files
        dir=`ls`
        for directory in $dir
        do
            # saving the even files
            directory_list_even=${directory_list_even}" "`echo $directory | grep -E "*[02468].txt"`
            directory_list_odd=${directory_list_odd}" "`echo $directory | grep -E "*[13579].txt"`
            #echo $directory_list
        done;
        
        echo directory_list_odd
        # Once i save the even files let's move their content
        for each_even_directory in $directory_list_even
        do
            # moving the even data to the dummy file
            head -n$n_val $each_even_directory >> dummy.txt
        done;
        # Put the odd data into the dummy file
        for each_odd_directory in $directory_list_odd
        do
            # moving the even data to the dummy file
            tail -n$n_val $each_odd_directory >> dummy.txt
        done;
        
        
    ;;

    4 )
        echo "Please enter the file Name"
        read file_name

        # Fetch the Currect date
        dat=`date +%Y-%m-%d`
        # Get the modified date of the file
        modi_date=`stat $file_name | grep Modify | awk -F" " '{print $2}'`

        #checking if greater than 24 hours or not
        echo "Modified Date: $modi_date"
        echo "Date: $dat"
        if [[ "$modi_date" == "$dat"  ]]
        then
        echo " Yes! They are created at the same day "
        else
        echo "Changing the modified date to current date"
        echo " " >> $file_name
          # Get the modified date of the file
        modi_date=`stat $file_name | grep Modify | awk -F" " '{print $2}'`
        echo "New Modified Date: $modi_date" 
        fi
    ;;

    5 )
        exit
    ;;
    *)
        echo " Invalid Input Selected "
    ;;
esac

done