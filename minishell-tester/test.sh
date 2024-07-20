#!/bin/bash

# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

exec_test() {
	# 全ての引数を改行で結合
	commands=$(printf "%s\n" "$@")

	# minishellで結合されたコマンドを実行
	printf "%b" "$commands" | ./minishell > $stdout_file 2> $stderr_file
	ES_1=$?
	TEST1=$(cat $stdout_file | grep -v "MINISHELL" | grep -v "heredoc") #Linux環境でなぜかプロンプトも標準出力に出力されてしまうのでとりあえずこれで除外
	ERR1=$(cat $stderr_file)

	# bashで結合されたコマンドを実行
	printf "%b" "$commands" | bash > $stdout_file 2> $stderr_file
	ES_2=$?
	TEST2=$(cat $stdout_file)
	ERR2=$(cat $stderr_file)

	# ERR1の各行がERR2の各行に含まれているか確認する
	is_err_same=true
	IFS=$'\n' ERR1=(${ERR1})
	IFS=$'\n' ERR2=(${ERR2})
	#行数が同じかどうか確認
	if [ ${#ERR1[@]} -ne ${#ERR2[@]} ]; then
		is_err_same=false
	fi
	#行ごとに比較
	for i in ${!ERR1[@]}; do
		if [[ "$ERR2" != *"$ERR1" ]]; then
			is_err_same=false
			break
		fi
	done

	# テスト結果の表示
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ] && [ $is_err_same == true ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		wrong_counter=$((wrong_counter + 1))
		printf " $BOLDRED%s$RESET" "✗ "
	fi

	# コマンドの表示
	printf "$CYAN"
	printf "\n%s" "$commands"
	printf "$RESET"

	# 出力結果の表示
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		printf "$BOLDRED Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf "$BOLDGREEN Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		printf "$BOLDRED Your exit status : $BOLDRED$ES_1$RESET\n"
		printf "$BOLDGREEN Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	if [ $is_err_same != true ]; then
		echo
		printf "$BOLDRED Your errmsg : \n%.20s\n$BOLDRED$ERR1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf "$BOLDGREEN Expected errmsg : \n%.20s\n$BOLDGREEN$ERR2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	echo
}

# minishellをビルド
make -C .. all
make -C .. clean
cp ../minishell .
chmod 755 minishell

# 権限の変更
chmod 000 no_permission
chmod 444 no_write_permission
chmod 222 no_read_permission

# hello作成
cc hello.c -o hello

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

# カウンターの初期化
wrong_counter=0

# テスト用のファイルを作成
stdout_file=$(mktemp)
stderr_file=$(mktemp)

# コマンドをテストする　必ず最後にexitを入れる
# exec_test 'sleep 5 | sleep 5' 'exit'
# exec_test 'pwd' 'exit 42'
# exec_test 'lsl' 'echo $?' '' '' '' '' '' '' '' '' '' '' '' '' 'ls' 'echo $?' 'exit'
# exec_test 'lsl' 'exit'
# exec_test 'env | grep TEST' 'export TEST=test' 'env | grep TEST' 'exit'


# コマンドをテストする
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

exec_test 'echo $"USER"' 'exit'
exec_test 'echo $PATH' 'exit'
exec_test 'echo $' 'exit'
exec_test 'echo $a"USER"' 'exit'
exec_test 'echo $""' 'exit'
exec_test '$USER' 'exit'
exec_test 'exit 24 | exit 42' 'echo $?' 'exit'
exec_test 'ls > out1 > out2' 'echo :out1' 'cat out1' 'echo :out2' 'cat out2' 'rm out1' 'rm out2' 'exit'
exec_test 'echo test1 > in1' 'echo test2 > in2' '< in1 < in2 cat' 'rm in1' 'rm in2' 'exit'
exec_test 'echo test2 > in2' '< in1 < in2 cat' 'rm in1' 'rm in2' 'exit'
exec_test 'echo test1 > in1' 'ls | cat < in1' 'rm in1' 'exit'
exec_test 'echo test1 > in1' 'echo test2 > in2' 'cat < in1 | cat < in2' 'rm in1' 'rm in2' 'exit'
exec_test '> newfile' 'ls' 'rm newfile' 'exit'
exec_test 'echo hello > no_permission' 'exit'
exec_test 'echo hello > $NOTHING' 'exit'
exec_test 'echo hello > ""' 'exit'

# # heredocもこれでテストできそう
exec_test 'cat << EOF' 'test' '$USER' 'EOF' 'exit'
exec_test '<< EOF << eof << eee cat' 'test1' 'eof' 'test2' 'eee' 'test3' 'EOF' 'test4' 'eof' 'test5' 'test6' 'eee' 'exit'
exec_test 'cat << EOF' '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test 'cat << "EOF"' '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test "cat << 'EOF'" '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test 'cat << E"O"F' '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test "cat << E'O'F" '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test "cat << E'O'F" '$USER' '"$USER"' \''$USER'\' 'EOF' 'exit'
exec_test 'cat << $PATH' '$USER' '"$USER"' \''$USER'\' '$PATH' 'exit'


# テスト結果の表示
echo
if [ $wrong_counter -eq 0 ]; then
	printf "$BOLDGREEN Perfect!!!$RESET\n"
else
	printf "$BOLDRED%d$RESET wrong result\n" $wrong_counter
fi

# 権限を戻す
chmod 644 no_permission
chmod 644 no_write_permission
chmod 644 no_read_permission

# テスト用のファイルを削除
rm -f $stdout_file $stderr_file