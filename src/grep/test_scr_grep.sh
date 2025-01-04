#!/bin/bash
grep="grep "
s21_grep="./grep"
SUCCESS=0
FAIL=0
COUNTER=0

RED="\033[31m"
GREEN="\033[32m"
BLUE="\033[36m"
ENDCOLOR="\033[0m"

grep_c="test_grep_file1.txt"

testing(){
    ./grep $var $grep_c> test_grep.log 
    grep $var $grep_c > test_grep.log
    if cmp -s test_grep.log test_grep.log
    then
    (( SUCCESS++ ))
    (( COUNTER++ ))

    echo "${GREEN}Test №$COUNTER SUCCESS${ENDCOLOR} ${BLUE}$grep $var $grep_c ${ENDCOLOR}"
    else
    (( FAIL++ ))
    (( COUNTER++ ))

    echo "${RED}Test №$COUNTER FAIL${ENDCOLOR} ${BLUE}$grep $var $grep_c ${ENDCOLOR}"
    fi
    rm -f ./test_grep.log ./test_grep.log
}

# проверки с одними флагами без значений
for var1 in v c l i h o n # 7 из 10
do  
    var="-$var1 he"
    testing "$var"
done

# проверки с несколькими флагами без значений
for var1 in v c l i h o n
do  
    for var2 in v c l i h o n
    do  
        if [ $var1 != $var2 ]
        then
            var="-$var1 -$var2 he"
            testing "$var"
        fi
    done
done

# проверки с одними флагами без значений двух файлов
for var1 in v c l i h # 7 из 10
do  
    var="-$var1 he test_grep_file1.txt"
    testing "$var test_grep_file1.txt"
done


# проверки для флага s который глушит сообщения об ошибках с файлом
for var1 in grep.c grep.h gre.b grep.tlsdf # 8 из 10
do  
    var="-s $var1 he"
    testing "$var"
done


# проверка на f флаг который задает паттерны
for var in "test_grep_file1.txt" "test_grep_file2.txt" "test_grep_file3.txt"
do  
    var="-f pattern.req"
    testing "$var"
done

echo "${GREEN}SUCCESS $SUCCESS ${ENDCOLOR} | ${RED} FAILED $FAIL${ENDCOLOR}";
