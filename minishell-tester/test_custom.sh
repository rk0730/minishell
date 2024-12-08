#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

# minishell_tester extras

# add test feedback by kazuki
exec_test 'cd ""' 'pwd' 'exit'
exec_test 'cd "" | cd ""' 'pwd' 'exit'
exec_test 'env | grep "PWD"' 'unset PWD' 'env | grep "PWD"' 'cd ..' 'env | grep "PWD"' 'export | grep "PWD"' 'exit'
exec_test 'env | grep "PWD"' 'unset PWD' 'env | grep "PWD"' 'cd ""' 'env | grep "PWD"' 'export | grep "PWD"' 'exit'
exec_test 'env | grep "PWD"' 'unset PWD' 'env | grep "PWD"' 'cd' 'env | grep "PWD"' 'export | grep "PWD"' 'exit'
exec_test 'env | grep "PWD"' 'unset PWD' 'env | grep "PWD"' 'sleep 3' 'env | grep "PWD"' 'export | grep "PWD"' 'exit'
exec_test 'env | grep "PWD"' 'unset PWD' 'env | grep "PWD"' 'env | grep "PWD"' 'export | grep "PWD"' 'exit'
exec_test 'env | grep "PWD"' 'unset PWD' 'env | grep "PWD"' 'cd no_such_file' 'env | grep "PWD"' 'export | grep "PWD"' 'exit'
exec_test 'env | grep "PWD"' 'unset PWD' 'env | grep "PWD"' 'cd "" no_such_file' 'env | grep "PWD"' 'export | grep "PWD"' 'exit'
exec_test 'cd ""' 'exit'
if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi