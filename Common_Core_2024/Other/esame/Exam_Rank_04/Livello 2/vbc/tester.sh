#!/bin/bash
# filepath: vbc_test.sh

# Colori per l'output
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

# Compila il programma
gcc -Wall -Wextra -Werror vbc.c -o vbc

# Funzione per testare un'espressione
test_expr() {
    expr="$1"
    expected="$2"
    
    echo -n "Testing '$expr': "
    result=$(./vbc "$expr" 2>&1)
    
    if [ "$result" == "$expected" ]; then
        echo -e "${GREEN}OK${RESET}"
    else
        echo -e "${RED}FAIL${RESET}"
        echo "  Expected: '$expected'"
        echo "  Got:      '$result'"
    fi
}

# Test di espressioni valide
echo -e "\n=== VALID EXPRESSIONS ===\n"
test_expr "1" "1"
test_expr "9" "9"
test_expr "2+3" "5"
test_expr "9+9" "18"
test_expr "3*4" "12"
test_expr "9*9" "81"

# Test di precedenza degli operatori
echo -e "\n=== OPERATOR PRECEDENCE ===\n"
test_expr "3*4+5" "17"     # (3*4)+5 = 17
test_expr "3+4*5" "23"     # 3+(4*5) = 23
test_expr "2+3*4+5" "19"   # 2+(3*4)+5 = 19
test_expr "9+8*7+6" "71"   # 9+(8*7)+6 = 71

# Test di parentesi
echo -e "\n=== PARENTHESES ===\n"
test_expr "(3+4)*5" "35"   # (3+4)*5 = 35
test_expr "(3*4)+5" "17"   # (3*4)+5 = 17
test_expr "(3)*(4)" "12"   # Parentesi semplici
test_expr "(3+4)*(5+6)" "77" # (3+4)*(5+6) = 7*11 = 77

# Test di parentesi nidificate
echo -e "\n=== NESTED PARENTHESES ===\n"
test_expr "((3+4)*5)" "35"
test_expr "(2*(3+4))" "14"
test_expr "(((((2+2)*2+2)*2+2)*2+2)*2+2)*2" "188"

# Test di errori sintattici
echo -e "\n=== SYNTAX ERRORS ===\n"
test_expr "1+" "Unexpected end of input"
test_expr "1+2)" "Unexpected token ')'"
test_expr "1+2(" "Unexpected token '('"
test_expr "(1+2" "Unexpected end of input"
test_expr "*1+2" "Unexpected token '*'"
test_expr "1**2" "Unexpected token '*'"
test_expr "1++2" "Unexpected token '+'"
test_expr "()" "Unexpected token ')'"

# Test di caratteri non validi
echo -e "\n=== INVALID CHARACTERS ===\n"
test_expr "a" "Unexpected token 'a'"
test_expr "1+a" "Unexpected token 'a'"
test_expr "1@2" "Unexpected token '@'"

# Test di casi limite
echo -e "\n=== EDGE CASES ===\n"
test_expr "" "Unexpected end of input"
test_expr "((((((((((1+1)))))))))))" "Unexpected token ')'"  # 10 livelli di parentesi

echo -e "\nTest completati!"