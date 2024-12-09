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
exec_test 'echo $OLDPWD' 'cd | ls' 'echo $OLDPWD' 'echo $?' 'exit'
exec_test 'echo $OLDPWD' 'ls | cd ..' 'echo $OLDPWD' 'echo $?' 'exit'
exec_test 'echo $OLDPWD' 'ls | cd hello | cat' 'echo $OLDPWD' 'echo $?' 'exit'
exec_test 'echo $OLDPWD' 'ls | cd no_such_dir | cat' 'echo $OLDPWD' 'echo $?' 'exit'
exec_test 'echo $PWD' 'cd | ls' 'echo $PWD' 'echo $?' 'exit'
exec_test 'echo $PWD' 'ls | cd ..' 'echo $PWD' 'echo $?' 'exit'
exec_test 'echo $PWD' 'ls | cd hello | cat' 'echo $PWD' 'echo $?' 'exit'
exec_test 'echo $PWD' 'ls | cd no_such_dir | cat' 'echo $PWD' 'echo $?' 'exit'
exec_test 'echo hello | cd ..' 'echo $?'  'exit'
exec_test 'mkdir dir' 'cd dir' 'rmdir ../dir' 'pwd' 'cd .' 'pwd' 'echo $?' 'exit'
exec_test 'mkdir dir' 'cd dir' 'rmdir ../dir' 'pwd' 'cd test test' 'pwd' 'echo $?' 'exit'
exec_test 'mkdir test' 'cd test' 'pwd' 'rmdir ../test' 'pwd' 'cd .' 'pwd' 'echo $?' 'exit'
exec_test 'mkdir test' 'cd test' 'pwd' 'rmdir ../test' 'pwd' 'cd test test' 'pwd' 'echo $?' 'exit'
# add test feedback by kazuki
exec_test 'cd ""' 'pwd' 'exit'
exec_test 'cd "" | cd ""' 'pwd' 'exit'
exec_test 'env | grep "PWD"' 'unset PWD' 'env | grep "PWD"' 'cd ..' 'env | grep "PWD"' 'export | grep "PWD"' 'exit'
exec_test 'cd ""' 'exit'

exec_test 'unset $OLDPWD' 'echo $OLDPWD' 'cd | ls' 'echo $OLDPWD' 'echo $?' 'exit'
exec_test 'unset $OLDPWD' 'echo $OLDPWD' 'ls | cd ..' 'echo $OLDPWD' 'echo $?' 'exit'
exec_test 'unset $OLDPWD' 'echo $OLDPWD' 'ls | cd no_such_dir | cat' 'echo $OLDPWD' 'echo $?' 'exit'
exec_test 'unset $PWD' 'echo $PWD' 'cd | ls' 'echo $PWD' 'echo $?' 'exit'
exec_test 'unset $PWD' 'echo $PWD' 'ls | cd ..' 'echo $PWD' 'echo $?' 'exit'
exec_test 'unset $PWD' 'echo $PWD' 'ls | cd hello | cat' 'echo $PWD' 'echo $?' 'exit'
exec_test 'unset $PWD' 'echo $PWD' 'ls | cd no_such_dir | cat' 'echo $PWD' 'echo $?' 'exit'

exec_test 'echo $OLDPWD' 'cd minishell-tester' 'echo $OLDPWD' 'echo $?' 'exit'
exec_test 'echo $OLDPWD' 'cd ..' 'echo $OLDPWD' 'echo $?' 'exit'
exec_test 'echo $OLDPWD' 'cd no_such_file' 'echo $OLDPWD' 'echo $?' 'exit'
exec_test 'echo $PWD' 'cd minishell-tester' 'echo $PWD' 'echo $?' 'exit'
exec_test 'echo $PWD' 'cd ..' 'echo $PWD' 'echo $?' 'exit'
exec_test 'echo $PWD' 'cd no_such_file' 'echo $PWD' 'echo $?' 'exit'
exec_test 'echo $PWD' 'ls | cd no_such_dir | cat' 'echo $PWD' 'echo $?' 'exit'
if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi