#! /bin/bash
GREEN="\033[1;32m"
RED="\033[1;31m"
BLUE="\033[1;34m"
RESET="\033[0m"

if [[ ! -x .././push_swap ]]; then
    echo -e "${RED}File push_swap not found or not executable${RESET}"
    exit 1
fi

if [[ ! -x ./checker_linux ]]; then
    echo -e "${RED}File checker_linux not found or not executable${RESET}"
    exit 1
fi

if [[ -z $1 ]]; then
    echo -e "${RED}Usage: ./100_num_checker.sh [number of tests]${RESET}"
    exit 1
fi

if [[ $1 -lt 1 ]]; then
	echo -e "${RED}Number of tests must be a number greater than 0${RESET}"
	exit 1
fi

tests=$1
n_tests=0
sum_moves=0
echo "" > failed_test_100.txt
echo "" > passed_test_100.txt

for ((i = 0; i < tests; i++)); do
	ARG=`seq 0 100 | shuf -n 100`
	moves=`.././push_swap $ARG`
	tot_moves=$(if [[ -n $moves ]]; then echo "$moves" | wc -l; else echo 0; fi)
	checker=$(if [[ -n $moves ]]; then echo "$moves"; else echo -n ""; fi | ./checker_linux $ARG 2>/dev/null)
	sum_moves=$((sum_moves + tot_moves))
	n_tests=$((n_tests + 1))
	if (( $tot_moves > 700 )); then
		echo -en "${RED}KO $tot_moves moves${RESET}"
		echo "Moves: $tot_moves" >> failed_test_100.txt
		echo $ARG >> failed_test_100.txt
		echo "" >> failed_test_100.txt
	else
		echo -en "${GREEN}OK $tot_moves moves${RESET}"
		echo "Moves: $tot_moves" >> passed_test_100.txt
		echo $ARG >> passed_test_100.txt
		echo "" >> passed_test_100.txt
	fi
	if [[ $checker == *OK* ]]; then
		echo -e ",${GREEN} checker OK ${RESET}"
	else
		echo -e ",${RED} checker KO ${RESET}"
fi
done

avg_moves=$((sum_moves / n_tests))
echo -e "${BLUE}Moves average in $n_tests tests: $avg_moves${RESET}"
echo -e "${BLUE}Failed tests in 'failed_test_100.txt' file${RESET}"
echo -e "${BLUE}Success tests in 'passed_test_100.txt' file${RESET}"
