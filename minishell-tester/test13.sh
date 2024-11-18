#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

# pre_cmdモジュールのテスト

exec_test 'export foo="a   b"' 'echo $foo' 'echo "$foo"' './argv $foo' './argv "$foo"' 'exit'
exec_test 'export TEST="-n hello"' 'env | grep TEST' 'echo $TEST' 'exit'
exec_test 'export TEST="| grep test"' 'ls $TEST' 'unset TEST' 'exit'
exec_test 'cat < file1 file2' 'exit'
exec_test 'export TEST="file1 file2"' 'cat < $TEST' 'unset TEST' 'exit'
exec_test 'export TEST="file1	file2"' 'cat < $TEST' 'unset TEST' 'exit'
exec_test 'export TEST="file1 file2"' 'cat < "$TEST" > out' 'unset TEST' 'exit'
exec_test 'export TEST="out1 > out2"' 'ls > $TEST' 'unset TEST' 'exit'
exec_test 'ls|  	  |ls' 'exit'
exec_test "export TEST='out1 out2'" 'ls > "out$TEST"' 'cat "outout1 out2"' 'rm "outout1 out2"' 'unset TEST' 'exit'
exec_test 'export TEST="out1 out2"' 'ls > out$TEST' 'unset TEST' 'exit'
exec_test 'export TEST="'"'out1 out2'"'"' 'ls > out$TEST' 'echo out$TEST' 'echo $TEST$?out' 'unset TEST' 'exit'
exec_test 'export TEST="'"''"'"' 'ls > out$TEST' 'echo out$TEST' "cat out''" 'rm out$TEST' 'unset TEST' 'exit'
exec_test 'export TEST="'"'1'"'"' 'ls > out$TEST' 'echo out$TEST' "cat out'1'" 'rm out$TEST' 'unset TEST' 'exit'
exec_test 'export TEST="'"'123'"'"' 'ls > out$TEST' 'echo out$TEST' "cat out'123'" 'rm out$TEST' 'unset TEST' 'exit'
exec_test 'export TEST="'"'1 23'"'"' 'ls > out$TEST' 'echo out$TEST' 'unset TEST' 'exit'
exec_test 'export TEST=test' 'echo $TESTa' 'unset TEST' 'exit'
exec_test "ls > out''" 'ls' 'rm out' 'exit'
exec_test 'export TEST="'"''"'"' 'ls > out$TEST' 'ls' 'rm "'"out''"'"' 'exit'
exec_test 'ls > "out1"out2'"'out3'" 'ls' 'rm out1out2out3' 'exit'
exec_test 'export TEST="'"''"'"' 'ls > "out1"out2'"'out3'"'$TEST' 'ls' 'rm "'"out1out2out3''"'"' 'exit'
exec_test 'export TEST="'"''"'"' 'ls > "out1out2'"'"'out3"$TEST' 'ls' 'rm "'"out1out2'out3''"'"' 'exit'
exec_test 'export TEST='"'"'"$USER"   "'"'" 'echo $TEST"$USER"$TEST' 'exit'

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi