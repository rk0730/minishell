#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi


# exec_test 'touch newfile' 'echo hello>newfile' 'cat newfile' 'rm newfile' 'exit'
# exec_test 'touch newfile' 'env > newfile' 'cat newfile' 'rm newfile' 'exit'
# exec_test 'echo a > test1 b' 'echo > test2 "d	ef"' 'cat test1 > test3 test2' 'cat test3' 'cat test2' 'exit'
# exec_test 'echo a > test1 b' 'echo > test2 "d	ef"' 'cat test1 > test3 > test2' 'cat test3' 'cat test2' 'exit'
# exec_test 'export TEST="file1	file2"' 'cat < $TEST' 'unset TEST' 'exit'
# exec_test 'ls|  	  |ls' 'exit'
# exec_test 'touch newfile' 'echo hello>newfile' 'cat <"newfile"<'"'new'file>"'"out"'"''" 'rm newfile out' 'exit'
# exec_test 'touch newfile' 'cat << EOF < newfile > newfile' 'test' 'EOF' 'cat newfile' 'rm newfile' 'exit'
# exec_test 'touch newfile' 'cat < newfile << EOF > newfile' 'test' 'EOF' 'cat newfile' 'rm newfile' 'exit'

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi