#!/bin/bash

# MINISHELL-TESTER

# メモリリークを見るかどうか
declare is_leak_test=false

# 引数が渡されている時
if [ $# > 0 ]; then
	if [ "$1" == "leak" ]; then
		is_leak_test=true
	fi
fi

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

# カウンター
declare wrong_counter
declare test_counter

# テスト用のファイル
declare stdout_file
declare stderr_file

start_test() {
	# ログファイルのクリア
	> result.log

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

	if [ "$is_leak_test" == true ]; then
		printf "$BOLDMAGENTA Memory leak test$RESET\n\n"
	fi
	# カウンターの初期化
	wrong_counter=0
	test_counter=0

	# テスト用のファイルを作成
	stdout_file=$(mktemp)
	stderr_file=$(mktemp)
}

exec_test() {
	test_counter=$((test_counter + 1))
	# 全ての引数を改行で結合
	commands=$(printf "%s\n" "$@")

	# minishellで結合されたコマンドを実行
	printf "%b" "$commands" | ./minishell > $stdout_file 2> $stderr_file
	ES_1=$?
	TEST1=$(cat $stdout_file | grep -v "MINISHELL" | grep -v "heredoc >" | grep -v -x "exit") #Linux環境でなぜかプロンプトも標準出力に出力されてしまうのでとりあえずこれで除外 exitも同様
	# ERR1=$(cat $stderr_file)
	ERR1=$(tr -d '\0' < "$stderr_file")

	# bashで結合されたコマンドを実行
	printf "%b" "$commands" | bash > $stdout_file 2> $stderr_file
	ES_2=$?
	# TEST2=$(cat $stdout_file)
	TEST2=$(tr -d '\0' < "$stdout_file")
	# ERR2=$(cat $stderr_file)
	ERR2=$(tr -d '\0' < "$stderr_file")

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

	# メモリリークのテスト
	declare ES_VAL
	declare FD_LEAK
	if [ "$is_leak_test" == true ]; then
		# メモリリークが起きた時のステータスコードを決める
		VALGRIND_ERROR=$(($ES_1 + 1))
		# Valgrindで結合されたコマンドを実行
		printf "%b" "$commands" | valgrind --leak-check=full --track-fds=yes --error-exitcode=$VALGRIND_ERROR ./minishell > $stdout_file 2> $stderr_file
		ES_VAL=$?
		# fdリークが起きているか確認
		if grep -a -q "Open file descriptor" $stderr_file; then
			FD_LEAK=true
		else
			FD_LEAK=false
		fi
	fi

	# テスト結果を変数に格納
	declare TEST_RESULT
	declare LEAK_TEST_RESULT
	# 出力とエラー出力が正しいかどうか
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ] && [ "$is_err_same" == true ]; then
		TEST_RESULT=ok
	else
		TEST_RESULT=failed
	fi
	# メモリリークのテスト結果
	if [ "$is_leak_test" == false ]; then
		LEAK_TEST_RESULT=ok
	elif [ "$ES_1" -eq "$ES_VAL" ] && [ "$FD_LEAK" == false ]; then
		LEAK_TEST_RESULT=ok
	else
		if [ "$ES_1" -ne "$ES_VAL" ] && [ "$FD_LEAK" == true ]; then
			LEAK_TEST_RESULT=both
		elif [ "$ES_1" -ne "$ES_VAL" ]; then
			LEAK_TEST_RESULT=memory
		else
			LEAK_TEST_RESULT=fd
		fi
	fi

	# コンソールにテスト結果を表示
	if [ "$TEST_RESULT" == "ok" ] && [ "$LEAK_TEST_RESULT" == "ok" ]; then
		# 結果があっていてリークもなし
		printf "$BOLDGREEN%d: %s$RESET" $test_counter "OK"
	elif [ "$TEST_RESULT" == "failed" ]; then
		# 間違い
		printf "$BOLDRED%d: %s$RESET" $test_counter "KO"
		wrong_counter=$((wrong_counter + 1))
	else
		# 結果はあってるがリークがある
		printf "$BOLDYELLOW%d: %s$RESET" $test_counter "LEAKSKO"
		wrong_counter=$((wrong_counter + 1))
	fi

	# コマンドの表示
	printf "$CYAN"
	printf "\n%s" "$commands"
	printf "$RESET"
	echo
	echo

	# result.log にテスト結果を書き込む
	if [ "$TEST_RESULT" != "ok" ] || [ "$LEAK_TEST_RESULT" != "ok" ]; then
		# 何かしらのミスがあるのでエラーコマンドを result.log に書き込む
		echo "---------------Command-------------------" >> result.log
		echo "$commands" >> result.log
	fi
	# 結果が違ったものを result.log に書き込む
	if [ "$TEST1" != "$TEST2" ]; then
		echo "--------------Your output----------------" >> result.log
		echo "$TEST1" >> result.log
		echo "-------------Expected output-------------" >> result.log
		echo "$TEST2" >> result.log
		# echo "-------------output diff-------------" >> result.log
		# diff <(echo "$TEST1") <(echo "$TEST2") >> result.log
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo "------------Your exit status-------------" >> result.log
		echo "$ES_1" >> result.log
		echo "-----------Expected exit status----------" >> result.log
		echo "$ES_2" >> result.log
	fi
	if [ "$is_err_same" != true ]; then
		echo "-----------Your error messages-----------" >> result.log
		echo "$ERR1" >> result.log
		echo "---------Expected error messages---------" >> result.log
		echo "$ERR2" >> result.log
	fi
	# リークのテスト結果を result.log に書き込む
	if [ "$LEAK_TEST_RESULT" != "ok" ]; then
		echo "--------------leak summary--------------" >> result.log
		if [ "$LEAK_TEST_RESULT" == "both" ]; then
			echo "memory leak detected" >> result.log
			echo "fd leak detected" >> result.log
		elif [ "$LEAK_TEST_RESULT" == "memory" ]; then
			echo "memory leak detected" >> result.log
		elif [ "$LEAK_TEST_RESULT" == "fd" ]; then
			echo "fd leak detected" >> result.log
		fi
	fi

	if [ "$TEST_RESULT" != "ok" ] || [ "$LEAK_TEST_RESULT" != "ok" ]; then
		# 何かしらのミスがあったので区切りを result.log に書き込む
		echo "-----------------------------------------" >> result.log
		echo "" >> result.log
		echo "" >> result.log
	fi
	# 出力結果の表示
	# if [ "$TEST1" != "$TEST2" ]; then
	# 	echo
	# 	printf "$BOLDRED Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	# 	printf "$BOLDGREEN Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	# fi
	# if [ "$ES_1" != "$ES_2" ]; then
	# 	echo
	# 	printf "$BOLDRED Your exit status : $BOLDRED$ES_1$RESET\n"
	# 	printf "$BOLDGREEN Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	# fi
	# if [ $is_err_same != true ]; then
	# 	echo
	# 	printf "$BOLDRED Your errmsg : \n%.20s\n$BOLDRED$ERR1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	# 	printf "$BOLDGREEN Expected errmsg : \n%.20s\n$BOLDGREEN$ERR2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	# fi
	# echo
}

end_test() {
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
}