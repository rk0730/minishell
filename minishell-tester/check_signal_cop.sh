#!/bin/bash

# テスト用のファイルを作成
declare stdout_file
declare stderr_file

# 一時ファイルを作成
# stdout_file=$(mktemp)
# stderr_file=$(mktemp)
stdout_file="out"
stderr_file="error"

EXECUTE_FILE="../minishell"

# # 標準出力と標準エラーをそれぞれファイルにリダイレクト
# printf "%b" "test >> a" | $EXECUTE_FILE > $stdout_file 2> $stderr_file

# # 結果を標準出力ファイルから処理する
# TEST1=$(grep -v "MINISHELL" $stdout_file | grep -v "heredoc >" | grep -v -x "exit")

# # 結果を表示
# echo "$TEST1"

# 結果ファイルを削除（クリーンアップ）
# rm -f $stdout_file $stderr_file


# pid=$!
# sleep 1
# # プロセスにSIGINT（Ctrl+C）を送って終了させる
# kill -SIGINT $pid


# minishellを起動し、終了しないように無限ループを使う
echo "test >> a" | $EXECUTE_FILE

# # 結果を標準出力ファイルから処理する
# TEST1=$(grep -v "MINISHELL" $stdout_file | grep -v "heredoc >" | grep -v -x "exit")

# 結果を表示
echo "$TEST1"

