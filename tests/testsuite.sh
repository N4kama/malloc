#!/bin/sh

testfile=tests/commands
printf "Tests are set on low difficulty, set it to high ? (y/n) : "
read diff
if [[ "$diff" =~ ^y.* ]]; then
    testfile=tests/commands_diff
fi

printf "Display mode is in 'discrete', set it to 'FULL' ? (y/n) : "
read show_my_res
echo

NBEXEC=0

success() {
    printf "RUNNING COMMAND $NBEXEC : \"%s\"\n" "$2"
    printf "RESULT : \e[92mOK\e[0m\n\n"
    if [[ "$show_my_res" =~ ^[y]+ ]]; then
        printf "STUDENT'S RESULT :\n$1\n\n"
    fi
}

failure() {
    printf "RUNNING COMMAND $NBEXEC : \"%s\"\n" "$3"
    printf "RESULT : \e[91mBAD\e[0m\n\n"
    if [[ "$show_my_res" =~ ^[y]+ ]]; then
        printf "STUDENT'S RESULT :\n\n$1\n\n"
	printf "SHOULD BE :\n\n$2\n\n"
    fi
}

while IFS='' read -a command; do
    ((NBEXEC++))
    my_res=$(LD_PRELOAD=./libmalloc.so $command)
    res=$($command)
    if test "$my_res" == "$res"; then
        success "$my_res" "$command"
    else
        failure "$my_res" "$res" "$command"
    fi
done < "$testfile"