#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

# pre_cmdモジュールのテスト

exec_test 'export foo="a   b"' 'echo $foo' 'echo "$foo"' './argv $foo' './argv "$foo"' 'exit'
exec_test 'export TEST="-n hello"' 'env | grep TEST' 'echo $TEST' 'exit'
exec_test 'export TEST="| grep test"' 'ls $TEST' 'unset TEST' 'exit'
exec_test 'export TEST="file1 file2"' 'cat < $TEST' 'unset TEST' 'exit'
exec_test 'export TEST="file1	file2"' 'cat < $TEST' 'unset TEST' 'exit'
exec_test 'export TEST="file1 file2"' 'cat < "$TEST" > out' 'unset TEST' 'exit'
exec_test 'export TEST="out1 > out2"' 'ls > $TEST' 'unset TEST' 'exit'
exec_test 'ls|  	  |ls' 'exit'

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi