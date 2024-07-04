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

# minishellをビルド
# make -C ..
cp ../minishell .
chmod 755 minishell

exec_test() {
	# 全ての引数を改行で結合
	commands=$(printf "%s\n" "$@")
	# commands=$(printf "%b" "$commands\nexit")

	# minishellで結合されたコマンドを実行
	TEST1=$(printf "%b" "$commands" | ./minishell 2>/dev/null)
	ERR1=$(printf "%b" "$commands" | ./minishell 2>&1 1>/dev/null)
	ES_1=$?

	# bashで結合されたコマンドを実行
	TEST2=$(printf "%b" "$commands" | bash 2>/dev/null)
	ERR2=$(printf "%b" "$commands" | bash 2>&1 1>/dev/null)
	ES_2=$?

	# テスト結果の表示
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
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
	if [ -n "$ERR1" ] || [ -n "$ERR2" ]; then
		echo
		printf "$BOLDRED Your errmsg : \n%.20s\n$BOLDRED$ERR1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf "$BOLDGREEN Expected errmsg : \n%.20s\n$BOLDGREEN$ERR2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	echo
	sleep 0.1
}

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

# コマンドをテストする　必ず最後にexitを入れる
exec_test 'ls' 'exit'
exec_test 'pwd' 'exit 42'
exec_test 'lsl' 'echo $?' 'exit'
exec_test 'env | grep TEST' 'export TEST=test' 'env | grep TEST' 'exit'

