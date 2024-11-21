#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

# minishell_tester extras

exec_test '' 'exit'

exec_test 'cd $PWD' 'echo $?' 'exit'
exec_test 'cd $PWD hi ' 'echo $?' 'exit'
exec_test 'cd 123123' 'echo $?' 'exit'
exec_test 'unset HOME' 'cd' 'echo $?' 'exit'
exec_test 'cd ..' 'env | grep PWD' 'echo $?' 'exit'
exec_test 'pwd' 'cd | ls' 'pwd' 'echo $?' 'exit'
exec_test 'pwd' 'ls | cd ..' 'pwd' 'echo $?' 'exit'
exec_test 'pwd' 'ls | cd hello | cat' 'pwd' 'echo $?' 'exit'
exec_test 'pwd' 'ls | cd no_such_dir | cat' 'pwd' 'echo $?' 'exit'
exec_test 'echo hello | cd ..' 'echo $?'  'exit'
exec_test 'mkdir dir' 'cd dir' 'rmdir ../dir' 'pwd' 'cd .' 'pwd' 'echo $?' 'exit'
exec_test 'mkdir dir' 'cd dir' 'rmdir ../dir' 'pwd' 'cd test test' 'pwd' 'echo $?' 'exit'
exec_test 'mkdir test' 'cd test' 'pwd' 'rmdir ../test' 'pwd' 'cd .' 'pwd' 'echo $?' 'exit'
exec_test 'mkdir test' 'cd test' 'pwd' 'rmdir ../test' 'pwd' 'cd test test' 'pwd' 'echo $?' 'exit'
if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi