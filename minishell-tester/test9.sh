#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

# minishell_tester buitins

exec_test 'echo hello world' 'exit'
exec_test 'echo "hello world"' 'exit'
exec_test "echo 'hello world'" 'exit'
exec_test "echo hello'world'" 'exit'
exec_test 'echo hello""world' 'exit'
exec_test "echo ''" 'exit'
exec_test 'echo "$PWD"' 'exit'
exec_test 'echo '"'"'$PWD'"'" 'exit'
exec_test 'echo "aspas ->'"'"'"' 'exit'
exec_test 'echo "aspas -> '"'"' "' 'exit'
exec_test "echo 'aspas ->"'"'"'" 'exit'
exec_test "echo 'aspas -> "'"'" '" 'exit'
exec_test 'echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<"' 'exit'
exec_test "echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<'" 'exit'
exec_test 'echo "exit_code ->$? user ->$USER home -> $HOME"' 'exit'
exec_test 'echo '"'"'exit_code ->$? user ->$USER home -> $HOME'"'" 'exit'
exec_test 'echo "$"' 'exit'
exec_test "echo '$'" 'exit'
exec_test 'echo $' 'exit'
exec_test 'echo $?' 'exit'
exec_test 'echo $?HELLO' 'exit'
exec_test 'pwd' 'exit'
exec_test 'pwd oi' 'exit'
exec_test 'export hello' 'exit'
exec_test 'export HELLO=123' 'exit'
exec_test 'export A-' 'exit'
exec_test 'export HELLO=123 A' 'exit'
exec_test 'export HELLO="123 A-"' 'exit'
exec_test 'export hello world' 'exit'
exec_test 'export HELLO-=123' 'exit'
exec_test 'export =' 'exit'
exec_test 'export 123' 'exit'
exec_test 'unset' 'exit'
exec_test 'unset HELLO' 'exit'
exec_test 'unset HELLO1 HELLO2' 'exit'
exec_test 'unset HOME' 'exit'
exec_test 'unset PATH' 'exit'
exec_test 'unset SHELL' 'exit'
exec_test 'cd $PWD' 'exit'
exec_test 'cd $PWD hi ' 'exit'
exec_test 'cd 123123' 'exit'
exec_test 'exit 123'
exec_test 'exit 298'
exec_test 'exit +100'
exec_test 'exit "+100"'
exec_test 'exit +"100"'
exec_test 'exit -100'
exec_test 'exit "-100"'
exec_test 'exit -"100"'
exec_test 'exit hello'
exec_test 'exit 42 world' 'exit'

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi