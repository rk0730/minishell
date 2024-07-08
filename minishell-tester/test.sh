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
	TEST1=$(cat $stdout_file)
	ERR1=$(cat $stderr_file)

	# bashで結合されたコマンドを実行
	printf "%b" "$commands" | bash > $stdout_file 2> $stderr_file
	ES_2=$?
	TEST2=$(cat $stdout_file)
	ERR2=$(cat $stderr_file)
	# エラーメッセージの整形（各行:で分割し、3番目以降のフィールドを取得）
	ERR2=$(echo "$ERR2" | cut -d':' -f3- | sed 's/^ //')

	# テスト結果の表示
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ] && [ "$ERR1" == "$ERR2" ]; then
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
	if [ "$ERR1" != "$ERR2" ]; then
		echo
		printf "$BOLDRED Your errmsg : \n%.20s\n$BOLDRED$ERR1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf "$BOLDGREEN Expected errmsg : \n%.20s\n$BOLDGREEN$ERR2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	echo
}

# minishellをビルド
make -C ..
cp ../minishell .
chmod 755 minishell

# 権限の変更
chmod 000 no_permission
chmod 444 no_write_permission
chmod 222 no_read_permission

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
exec_test 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa' 'exit'
exec_test 'echo hello' 'exit'
exec_test 'echo hello world' 'exit'
exec_test 'echo hello      world!' 'exit'
exec_test 'cat no_write_permission' 'exit'
exec_test 'cat no_read_permission' 'exit'
exec_test 'cat no_such_file' 'exit'


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