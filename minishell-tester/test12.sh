#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

# minishell_tester extras

exec_test '' 'exit'
exec_test '$PWD' 'exit'
exec_test '$EMPTY' 'exit'
exec_test '$EMPTY echo hi' 'exit'
exec_test './test_files/invalid_permission' 'exit'
exec_test './missing.out' 'exit'
exec_test 'missing.out' 'exit'
exec_test '"aaa"' 'exit'
exec_test 'test_files' 'exit'
exec_test './test_files' 'exit'
exec_test '/test_files' 'exit'
exec_test 'minishell.h' 'exit'
exec_test '$' 'exit'
exec_test '$?' 'exit'
exec_test 'README.md' 'exit'


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi