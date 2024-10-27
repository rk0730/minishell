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
	TEST1=$(cat $stdout_file | grep -v "MINISHELL" | grep -v "heredoc" | grep -v "exit") #Linux環境でなぜかプロンプトも標準出力に出力されてしまうのでとりあえずこれで除外 exitも同様
	ERR1=$(cat $stderr_file)

	# bashで結合されたコマンドを実行
	printf "%b" "$commands" | bash > $stdout_file 2> $stderr_file
	ES_2=$?
	TEST2=$(cat $stdout_file)
	ERR2=$(cat $stderr_file)

	# ERR1の各行がERR2の各行に含まれているか確認する
	is_err_same=true
	IFS=$'\n' ERR_ARRAY1=(${ERR1})
	IFS=$'\n' ERR_ARRAY2=(${ERR2})
	#行数が同じかどうか確認
	if [ ${#ERR_ARRAY1[@]} -ne ${#ERR_ARRAY2[@]} ]; then
		is_err_same=false
	fi
	#行ごとに比較
	for i in ${!ERR_ARRAY1[@]}; do
		if [[ "$ERR_ARRAY2" != *"$ERR_ARRAY1" ]]; then
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
rm -f minishell
make -C .. re
make -C .. clean
cp ../minishell . 
chmod 755 minishell

# 権限の変更
chmod 000 no_permission
chmod 444 no_write_permission
chmod 222 no_read_permission

# 実行ファイル作成
cc hello.c -o hello
cc argv.c -o argv

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

# can't check error status
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
# sintax errorだからスルーかな
# exec_test 'export %& | echo $%& $B' 'echo $?' 'exit'
# exec_test 'export %&=9 | echo $%& $B' 'echo $?' 'exit'
# exec_test 'export _9=%& | echo $_9 $B' 'echo $?' 'exit'
exec_test 'export _9=1 | echo $_9' 'echo $?' 'exit'
# # cdテスト
# exec_test 'unset HOME' 'cd' 'exit'
# exec_test 'cd ..' 'env | grep PWD' 'exit'

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
rm -f minishell