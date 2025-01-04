#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

executable_command=("./cat")
sys_command=("cat")
test_file="test_cat_file.txt"

flags=("b" "e" "n" "s" "t")

run_test() {
    param=$(echo "$@" | sed "s/FLAGS/$var/")
    "${executable_command[@]}" $param > "${executable_command[@]}".log
    "${sys_command[@]}" $param > "${sys_command[@]}".log
    DIFF="$(diff -s "${executable_command[@]}".log "${sys_command[@]}".log)"
    let "COUNTER++"
    if [ "$DIFF" == "Files "${executable_command[@]}".log and "${sys_command[@]}".log are identical" ]
    then
        let "SUCCESS++"
        echo "$COUNTER - Success $param"
    else
        let "FAIL++"
        echo "$COUNTER - Fail $param"
    fi
    rm -f "${executable_command[@]}".log "${sys_command[@]}".log
}

echo "^^^^^^^^^^^^^^^^^^^^^^^"
echo "TESTS WITH NORMAL FLAGS"
echo "^^^^^^^^^^^^^^^^^^^^^^^"
printf "\n"

# Тесты с одним флагом
for flag in "${flags[@]}"; do
    var="-$flag"
    run_test "FLAGS $test_file"
done

# Тесты с двумя флагами
for flag1 in "${flags[@]}"; do
    for flag2 in "${flags[@]}"; do
        if [ $flag1 != $flag2 ]; then
            var="-$flag1 -$flag2"
            run_test "FLAGS $test_file"
        fi
    done
done

# Тесты с тремя флагами
for flag1 in "${flags[@]}"; do
    for flag2 in "${flags[@]}"; do
        for flag3 in "${flags[@]}"; do
            if [ $flag1 != $flag2 ] && [ $flag2 != $flag3 ] && [ $flag1 != $flag3 ]; then
                var="-$flag1 -$flag2 -$flag3"
                run_test "FLAGS $test_file"
            fi
        done
    done
done

# Тесты с четырьмя флагами
for flag1 in "${flags[@]}"; do
    for flag2 in "${flags[@]}"; do
        for flag3 in "${flags[@]}"; do
            for flag4 in "${flags[@]}"; do
                if [ $flag1 != $flag2 ] && [ $flag2 != $flag3 ] && [ $flag1 != $flag3 ] && [ $flag1 != $flag4 ] && [ $flag2 != $flag4 ] && [ $flag3 != $flag4 ]; then
                    var="-$flag1 -$flag2 -$flag3 -$flag4"
                    run_test "FLAGS $test_file"
                fi
            done
        done
    done
done

echo "ПРОВАЛЕНО: $FAIL"
echo "ПРОЙДЕНО: $SUCCESS"
echo "ВСЕГО: $COUNTER"
printf "\n"

exit 0
