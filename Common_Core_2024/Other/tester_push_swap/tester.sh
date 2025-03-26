#!/bin/bash
#ARG=$(echo -e "\n")
##############CREDITS##############
#BY gpicchio
#Parsing checker: smontuor
#number_checker: tpicchio
#remember to chmod 777 *.sh

clear
#the makefile must be in the root, if u want to change it u have to change the path
make all -C ../

echo -e "\e[1;33mPress Enter to continue (parsing checker)\e[0m"
read

./test.sh "push_swap"

echo -e "\e[1;33mPress Enter to continue (3 number checker)\e[0m"
read
./3_num_checker.sh

echo -e "\e[1;33mPress Enter to continue (5 number checker)\e[0m"
read
./5_num_checker.sh

echo -e "\e[1;33mEnter number of tests (100 number checker)\e[0m"
read numero
./100_num_checker.sh $numero

echo -e "\e[1;33mEnter number of tests (500 number checker)\e[0m"
read numero
./500_num_checker.sh $numero