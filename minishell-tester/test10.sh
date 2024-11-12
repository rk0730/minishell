#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

# minishell_tester pipes

exec_test 'env | sort | grep -v SHLVL | grep -v ^_' 'exit'
exec_test 'cat ./test_files/infile_big | grep oi' 'exit'
exec_test 'cat minishell.h | grep ");"$' 'exit'
exec_test 'export GHOST=123 | env | grep GHOST' 'exit'


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi