source ./test_utils.sh

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	start_test
fi

# テスト5 必ず最後にexitを入れる

# export

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
exec_test 'export _ | echo $_ $B' 'echo $?' 'exit'
exec_test 'export %& | echo $%& $B' 'echo $?' 'exit'
exec_test 'export %&=9 | echo $%& $B' 'echo $?' 'exit'
exec_test 'export _9=%& | echo $_9 $B' 'echo $?' 'exit'


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi