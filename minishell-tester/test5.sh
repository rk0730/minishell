#!/bin/bash

source ./test_utils.sh

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	start_test
fi

# テスト5 必ず最後にexitを入れる

exec_test 'export A B C $ | echo $A' 'echo $?' 'exit'
exec_test 'export A=9 B=6 C=3 | echo $A=$B ' 'echo $?' 'exit'
exec_test 'export A=9 B=6 C=3 | export $A=$B | echo $A $B' 'echo $?' 'exit'
exec_test 'export A=9 B=6 C=3 | export A=$B | echo $A $B' 'echo $?' 'exit'
exec_test 'export A=9 B=6 C | export $C=$B | echo $A $B' 'echo $?' 'exit'
exec_test 'export A=9 B=6 C=3 | export $"C"=$B | echo $A $B' 'echo $?' 'exit'
exec_test 'export A=9 B=6 C=3 | export $'C'=$B | echo $A $B' 'echo $?' 'exit'
exec_test 'export A= | echo $A $B' 'echo $?' 'exit'
exec_test 'export A | echo $A $B' 'echo $?' 'exit'
exec_test 'export A=9 | echo $A $B' 'echo $?' 'exit'
exec_test 'export _9=9 | echo $A $B' 'echo $?' 'exit'
exec_test 'export _=9 | echo $_ $B' 'echo $?' 'exit'
exec_test 'export $' 'echo $?' 'exit'
exec_test 'export $ | echo test' 'echo $?' 'exit'
exec_test 'export $ K=9' 'echo $?' 'exit'
exec_test 'export $ K=9' 'echo $K' 'exit'
exec_test 'export 9K=9' 'echo $K' 'exit'
exec_test 'export 9_=9' 'echo $K' 'exit'
exec_test 'export 9K' 'echo $K' 'exit'
exec_test 'export K=9' 'echo $K' 'exit'
exec_test 'export K=9' 'export K+=9' 'echo $K' 'exit'
# sintax errorだからスルーかな
# exec_test 'export %& | echo $%& $B' 'echo $?' 'exit'
# exec_test 'export %&=9 | echo $%& $B' 'echo $?' 'exit'
# exec_test 'export _9=%& | echo $_9 $B' 'echo $?' 'exit'
exec_test 'export _9=1 | echo $_9' 'echo $?' 'exit'

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

exec_test 'env | grep _=' 'exit'
exec_test 'ls' 'echo $_' 'env | grep _=' 'exit'
exec_test 'pwd' 'echo $_' 'ls | ls' 'echo $_'  'exit'
exec_test 'echo $_' 'exit'
exec_test 'echo $USER' 'echo $_' 'exit'

# # cdテスト
# exec_test 'unset HOME' 'cd' 'exit'
# exec_test 'cd ..' 'env | grep PWD' 'exit'

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi