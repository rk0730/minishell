source ./test_utils.sh

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	start_test
fi

# テスト3 必ず最後にexitを入れる

# パイプ
exec_test 'ls | grep .c' 'exit'
exec_test '< no_such_file ls | wc' 'exit'
exec_test 'cat Makefile | grep minishell | sort' 'exit'
exec_test 'cat   hello.c | wc -cl  | wc   |  grep o  | sort | cat' 'exit'
exec_test 'cat hello.c | sort | wc | ls | cd | wc' 'pwd' 'exit'
exec_test 'ls|ls|ls|ls|ls|ls' 'exit'
exec_test 'echo test1 > in1' 'ls | cat < in1' 'rm in1' 'exit'
exec_test 'echo test1 > in1' 'echo test2 > in2' 'cat < in1 | cat < in2' 'rm in1' 'rm in2' 'exit'
exec_test 'cat < no_permission | ls > out | cat' 'ls' 'cat out' 'rm out' 'exit'
exec_test 'cat < no_permission|<no_read_permission cat| ls > out' 'ls' 'cat out' 'rm out' 'exit'
exec_test 'cat < no_permission | < no_read_permission cat | cat << EOF |cat|cat|cat' 'test' 'EOF' 'exit'
exec_test 'cat>no_permission<<EOF | cat' 'test' 'EOF' 'exit'
exec_test 'cat > no_permission | cat | ls|cat' 'exit'
exec_test 'cat <no_"read"_permission > no_write_"permission""" | ls | cat <<EOF | cat< no_permission|ls|cat<<eof' 'TEST' 'EOF' 'test' 'eof' 'exit'
exec_test 'cat < no_read_permission | cat << EOF | lsl | <<eof cat "|" ls | cat > no_write_permission' '1' 'EOF' '2' 'eof' 'exit'
exec_test 'env | grep USER' 'env | grep SHELL' 'env | grep PATH' 'exit'

exec_test 'env | grep TEST' 'export TEST=test' 'env | grep TEST' 'exit'
exec_test 'env | grep TEST' 'ls | export TEST=test' 'env | grep TEST' 'exit'
exec_test 'env | grep TEST' 'export TEST=test | env | grep USER=' 'env | grep TEST' 'exit'
exec_test 'export TEST=test' 'env | grep TEST' 'unset TEST | ls | echo 1' 'env | grep TEST' 'pwd | unset TEST | echo 2' 'env | grep TEST' 'unset TEST' 'env | grep TEST' 'exit'
exec_test 'export foo="a   b"' 'echo $foo' 'echo "$foo"' './argv $foo' './argv "$foo"' 'exit'
exec_test 'export foo=abc$USER' 'echo $foo' 'echo "$foo"' './argv $foo' './argv "$foo"' 'exit'
exec_test 'pwd' 'cd | ls' 'pwd' 'exit'
exec_test 'pwd' 'ls | cd ..' 'pwd' 'exit'
exec_test 'pwd' 'ls | cd hello | cat' 'pwd' 'exit'
exec_test 'pwd' 'ls | cd no_such_dir | cat' 'pwd' 'exit'
exec_test 'cat | ls' '' 'exit'


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi