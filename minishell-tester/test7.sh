#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

exec_test 'cat <"./test_files/infile_big" | echo hi' 'exit'
exec_test 'echo hi | cat <"./test_files/infile_big" | cat' 'exit'
exec_test 'grep hi "<infile" <         ./test_files/infile' 'echo $?' 'exit'
exec_test '$PWD' 'exit'
exec_test './test_files' 'exit'
exec_test './test_files/invalid_permission ' 'exit'
exec_test '/test_files' 'exit'
exec_test './missing.out' 'exit'

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi