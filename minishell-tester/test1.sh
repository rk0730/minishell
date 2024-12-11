#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

# テスト1 必ず最後にexitを入れる

exec_test '   ' 'exit'
exec_test '/bin/ls' 'exit'
exec_test '/bin/pwd' 'exit'
exec_test '/bin/echo' 'exit'
exec_test 'ls' 'exit'
exec_test 'pwd' 'exit'
exec_test './hello' 'exit'
exec_test 'lsll' 'exit'
exec_test 'exit'
exec_test 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa' 'exit'
exec_test 'echo hello' 'exit'
exec_test 'echo hello world' 'exit'
exec_test 'echo hello      world!' 'exit'
exec_test '   echo    hello               world!       ' 'exit'
exec_test 'lsl' 'echo $?' '' '' '' '' '' '' '' '' '' '' '' '' 'ls' 'echo $?' 'exit'
exec_test 'lsl' 'exit'
exec_test 'ls -a' 'exit'
exec_test 'cat no_write_permission' 'exit'
exec_test 'cat no_read_permission' 'exit'
exec_test 'cat no_such_file' 'exit'
exec_test 'echo $USER $SHELL' 'exit'
exec_test 'echo $USER $USERR $SHELL' 'exit'
exec_test 'echo $USER "$USERR" $SHELL' 'exit'
exec_test 'echo hello world      $USER' 'exit'
exec_test "echo 'hello world'    '42'   " 'exit'
exec_test 'echo "hello world"   " 42"   ' 'exit'
exec_test "echo '"'"hello world"'"'    '42'   " 'exit'
exec_test "echo hello'  world'" 'exit'
exec_test "echo hello'  world'"'"  42"' 'exit'
exec_test 'echo "$'"'USER'"'"' 'exit'
exec_test 'echo $'"'USER'" 'exit'
exec_test 'echo "$'"''"'"' 'exit'
exec_test 'echo "$"' 'exit'
exec_test 'echo '$'' 'exit'
exec_test 'echo $' 'exit'
exec_test 'echo $?' 'exit'
exec_test 'echo $?HELLO' 'exit'
exec_test 'lsl' 'echo $?' 'exit'
exec_test 'lsl' '$?' 'echo "$?""hello"' 'exit'
exec_test 'lsl' 'echo $?HELLO' 'exit'
exec_test 'echo $??' 'exit'
exec_test 'echo $??HELLO' 'exit'
exec_test 'lsl' 'echo $???' 'exit'
exec_test 'lsl' '$???' 'echo $?' 'exit'
exec_test 'lsl' 'echo $?abc' 'exit'
exec_test 'echo $"USER"' 'exit'
exec_test 'echo $PATH' 'exit'
exec_test 'echo $' 'exit'
exec_test 'echo $a"USER"' 'exit'
exec_test 'echo $""' 'exit'
exec_test '$USER' 'exit'
exec_test 'touch newfile' 'echo hello>newfile' 'cat newfile' 'rm newfile' 'exit'
exec_test 'touch newfile' 'echo hello>newfile' 'cat <"newfile"<'"'new'file>"'"out"'"''" 'rm newfile out' 'exit'
exec_test 'ls > out1 > out2' 'echo :out1' 'cat out1' 'echo :out2' 'cat out2' 'rm out1 out2' 'rm out2' 'exit'
exec_test 'echo test1 > in1' 'echo test2 > in2' '< in1 < in2 cat' 'rm in1' 'rm in2' 'exit'
exec_test 'echo test2 > in2' '< in1 < in2 cat' 'rm in1' 'rm in2' 'exit'
exec_test '> newfile' 'ls' 'rm newfile' 'exit'
exec_test 'echo hello > no_permission' 'exit'
exec_test 'echo hello > $NOTHING' 'exit'
exec_test 'echo hello > ""' 'exit'
exec_test 'echo $'USER'$' 'exit'
exec_test 'echo $"USER"$' 'exit'
exec_test 'echo "$USER'"'$'"'"' 'exit'
exec_test 'echo "$USER"$""' 'exit'
exec_test 'echo "$USER""$"' 'exit'
exec_test 'echo $' 'exit'
exec_test 'echo $""' 'exit'
exec_test 'echo $USER$' 'exit'
exec_test 'echo "$USER$"' 'exit'
exec_test 'echo "$USER$""$USER$"' 'exit'
exec_test 'echo $USER$1' 'exit'
exec_test 'echo $USER$11' 'exit'
exec_test 'echo $USER$a1' 'exit'
exec_test 'echo $USER$a111' 'exit'
exec_test 'echo $1' 'exit'
exec_test 'echo $""' 'exit'
exec_test 'echo $"a"' 'exit'
exec_test 'echo $USER$=9' 'exit'
exec_test 'echo $USER=9' 'exit'
exec_test 'echo $"USER=9"' 'exit'

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi