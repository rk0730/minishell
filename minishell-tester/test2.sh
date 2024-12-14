#!/bin/bash


if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	source ./test_utils.sh
	start_test
fi

# テスト2 必ず最後にexitを入れる

# heredoc
exec_test 'cat <<' 'exit'
exec_test 'cat << <<' 'exit'
exec_test 'cat << | cat << eof' 'exit'
exec_test 'cat << > | cat << <<' 'exit'
exec_test 'cat << >> | cat <<' 'exit'
exec_test 'cat << EOF | cat <<' '1' 'EOF' 'exit'
exec_test 'cat << | cat < no_such_file' 'exit'
exec_test 'cat << < no_such_file' 'exit'
exec_test 'cat << < no_such_file | cat << EOF' 'exit'
exec_test 'cat << < no_such_file | cat << ' 'exit'
exec_test 'cat < no_such_file << | cat << EOF' 'exit'
exec_test 'cat << EOF' 'test' '$USER' '$TEST' '$1' '$11' 'EOF' 'exit'
exec_test 'cat << EOF' '$a111111$' '"$USE'"'R'$"'"' '$""' '$"' 'EOF' 'exit'
exec_test '<< EOF << eof << eee cat' 'test1' 'eof' 'test2' 'eee' 'test3' 'EOF' 'test4' 'eof' 'test5' 'test6' 'eee' 'exit'
exec_test 'cat <<EOF' '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test 'cat <<"EOF"' '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test "cat <<'EOF'" '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test 'cat <<E"O"F' '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test "cat << E'O'F" '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test "cat << E'O'F" '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test 'cat <<$PATH' '$USER' '"$USER"' \''$USER'\' '$PATH' 'exit'

exec_test "cat << '"'"''$USER'"'" '$USER' "'"'"$USER"'"'" '"$USER"' '""$USER' '"$USER' 'exit'
exec_test "cat << '"'"$USER"'"'" '$USER' "'"'"$USER"'"'" '"$USER"' 'exit'
exec_test 'cat << "$USER"' '"$USER"' '$USER' 'exit'
exec_test 'cat << '"'"'$PA'"'"'TH' '$PATH' 'exit'
exec_test 'cat << '"'"'$PA'"'"'TH' '$USER' '$US"ER' '$USER' '"PATH' '$PATH""' 'TH' "''TH" "'"'$PA'"'"'TH' '$PATH' 'exit'
exec_test 'cat << '"'"'$PATH'"'" '$USER' '$US"ER' '"$PATH' '$PATH""' '$PATH' 'exit'
exec_test 'cat << $PATH' '$USER' '$US"ER' '"$PATH' '$PATH""' '$PATH' 'exit'
exec_test 'cat << EOF' '$_1' '$_2' '$_____?' '$_____1?' '$_____11' 'EOF' 'exit'




exec_test 'cat << EOF > out' 'test' 'EOF' 'cat out' 'rm out' 'exit'
exec_test 'echo test > out' 'cat << EOF >> out' 'test' 'EOF' 'cat out' 'rm out' 'exit'
exec_test 'cat << EOF < no_permission > out' 'test' 'EOF' 'cat out' 'rm out' 'exit'
exec_test 'cat << EOF < no_write_permission > no_write_permission' 'test' 'EOF' 'cat out' 'rm out' 'exit'
exec_test 'cat << EOF < no_write_permission' 'test' 'EOF' 'cat out' 'rm out' 'exit'
exec_test 'cat > no_write_permission < no_write_permission << EOF' 'test' 'EOF' 'cat out' 'rm out' 'exit'
exec_test 'cat > no_write_permission < no_permission << EOF' 'test' 'EOF' 'cat out' 'rm out' 'exit'
exec_test 'cat << EOF > out > out2' 'test' 'EOF' 'cat out' 'cat out2' 'rm out' 'rm out2' 'exit'
exec_test 'echo aaa > out1' 'cat << EOF > out > out2' 'test' 'EOF' 'cat out' 'cat out2' 'rm out out1 out2' 'exit'
exec_test 'touch newfile' 'cat << EOF < newfile > newfile' 'test' 'EOF' 'cat newfile' 'rm newfile' 'exit'
exec_test 'touch newfile' 'cat < newfile << EOF > newfile' 'test' 'EOF' 'cat newfile' 'rm newfile' 'exit'
exec_test 'cat << EOF' '$?' '"$?' '"$?"' '$USER' '"$USER"' 'EOF' 'exit'
exec_test 'lsl' 'cat << $?' '"$?' '"$?"' '$USER' '"$USER"' '$?' 'exit'
exec_test 'cat << $??' '$?' '"$?' '"$?"' '"$??"' '$???' '$??' 'exit'

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi