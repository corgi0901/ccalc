#!/bin/sh

test() {
    output=$(./ccalc "$1")
    if [ "$output" != "$2" ]; then
        echo "NG : $1 => $output (expected $2)"
    fi
}

# Number
test "123"      "123"
test "0123"     "123"
test "1.23"     "1.230000"
test "."        "0.000000"
test "-123"     "-123"
test "-1.23"    "-1.230000"
test "3.14000"  "3.140000"

# Arithmetic operations
# Add
test "1+1"      "2"
test "-3+5"     "2"
test "12+-3"    "9"
test "-10+-5"   "-15"
test "0.25+3"   "3.250000"

# Sub
test "100-10" "90"
test "-60-50" "-110"
test "35--40" "75"
test "-99--1" "-98"
test "1-3.50" "-2.500000"

# Mul
test "3*5"      "15"
test "-2*10"    "-20"
test "6*-8"     "-48"
test "-9*-3"    "27"
test "1.5*4"    "6.000000"

# Div
test "20/4"     "5"
test "-24/2"    "-12"
test "36/-10"   "-3"
test "-9/-3"    "3"
test "12.0/3.0" "4.000000"

# Complex
test "(1+3)"            "4"
test "((3*5))"          "15"
test "5*(3+4)"          "35"
test "(1+3)*(-3*5)"     "-60"
test "(4+6)*5"          "50"
test "((-3+4)*2)+10"    "12"
test "(0.15+3)*2+4"     "10.300000"

# Contain space
test "  1"                  "1"
test "  1 + 3  "            "4"
test "1 + 4*5   + 3 - -5"   "29"

# Error
test "a"        "Err"
test "123 a"    "Err"
test "12c4"     "Err"
test "1 2"      "Err"
test "((3+4)"   "Err"
test "--6"      "Err"
test "1 * / 4"  "Err"
test "1.24.56"  "Err"
test "1/0"      "Err"
test "10/0.0"   "Err"

echo "Finish"