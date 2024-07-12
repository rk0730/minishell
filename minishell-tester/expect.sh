#!/bin/sh

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

# 引数の数が1でない場合はエラーを出力して終了
if [ $# -ne 1 ]; then
	echo "Usage: $0 bash or minishell"
	exit 1
fi

run=$1

# 引数がbashかminishellかでwait変数（プロンプト）の値を変える
if [ $1 == "bash" ]; then
	wait="bash-3.2$ "
	rum="bash"
	printf "\n$BOLDMAGENTA%s$RESET\n\n" "bash"
elif [ $1 == "minishell" ]; then
	# minishellをビルド
	wait="MINISHELL$ "
	run="./minishell"
	make -C .. all
	make -C .. clean
	cp ../minishell .
	chmod 755 minishell
	printf "\n$BOLDMAGENTA%s$RESET\n\n" "minishell"
else
	echo "Usage: $0 bash or minishell"
	exit 1
fi

# 権限の変更
chmod 000 no_permission
chmod 444 no_write_permission
chmod 222 no_read_permission

# expectコマンドで対話的にテストする
# エラーの挙動やheredocの挙動はこれで確認できる
expect -c "

# タイムアウトを10秒に設定
set timeout 10

# 実行ファイルを起動
spawn $run
sleep 0.5

# プロンプトが表示されたらコマンドを送信
expect \"$wait\" { send \"lsl\n\" }
expect \"$wait\" { send \"cat no_permission\n\" }

expect \"$wait\" { send \"cat << EOF\n\" }
expect \"> \" { send \"test\n\" }
expect \"> \" { send \"EOF\n\" }

expect \"$wait\" { send \"cat << EOF\n\" }
expect \"> \" { send \"test\n\" }
expect \"> \" { send \"EOF\n\" }

expect \"$wait\" { send \"exit\n\" }
expect eof
"

# 権限を戻す
chmod 644 no_permission
chmod 644 no_write_permission
chmod 644 no_read_permission
