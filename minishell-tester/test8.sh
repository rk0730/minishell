#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

# 42のチャンネルで共有されていたてすと
# https://discord.com/channels/691903146909237289/813630632386625556/813643217424875552

exec_test 'export TEST="a=b=c=d"' 'env | grep TEST' 'echo $TEST' 'exit'
exec_test 'export TEST="-n hello"' 'env | grep TEST' 'echo $TEST' 'exit'
exec_test 'export PIPE="|"' 'echo $PIPE' 'ps -a $PIPE grep bash' 'exit'
exec_test 'echo $? | exit 42 | echo $?'  'exit'
exec_test 'echo hello | cd ..'  'exit'
exec_test 'export a=" "' 'echo$a-a' 'exit'
exec_test 'mkdir dir' 'cd dir' 'rmdir ../dir' 'pwd' 'cd .' 'pwd' 'exit'
exec_test 'echo "echo hello" > exe && chmod +x exe' 'ln -s exe symexe' 'chmod -h -x symexe' 'ls -l' './symexe ' 'exit'
exec_test 'exit -- 42' 'echo $?' 'exit'
exec_test 'exit 42 42' 'echo $?' 'exit'
exec_test 'exit a' 'echo $?' 'exit'
exec_test "export SHLVL=`printf '\t\n\v\f\r 42'`" 'echo $SHLVL' 'exit'
exec_test "export SHLVL=`printf '\t\n\v\f\r 42\v'`" 'echo $SHLVL' 'exit'
exec_test '> f0 echo > f1 > f2 > f3 abc' 'exit'
exec_test 'export test=""dklfjsdklfjk""' 'export | grep "declare -x test"' 'exit'
exec_test 'export TEST="TEST=aaaa"' '$TEST' 'exit'
exec_test 'echo -nnnnnnn hello' 'exit'
exec_test 'echo a > test1 b' 'echo > test2 "d	ef"' 'cat test1 > test3 test2' 'cat test3' 'cat test2' 'exit'
exec_test 'echo a > test1 b' 'echo > test2 "d	ef"' 'cat test1 > test3 > test2' 'cat test3' 'cat test2' 'exit'
exec_test 'export $nothing $nothing $nothing $nothing' 'exit'
exec_test 'export PWD="test"' 'echo $PWD' 'exit'

# https://discord.com/channels/691903146909237289/813630632386625556/883633459367657503 これなに


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi