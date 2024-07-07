#!/bin/sh

# 引数の数が1でない場合はエラーを出力して終了
if [ $# -ne 1 ]; then
	echo "Usage: $0 bash or $0 ./minishell"
	exit 1
fi

run=$1

# 引数がbashかminishellかでwait変数（プロンプト）の値を変える
if [ $1 == "bash" ]; then
	wait="bash-3.2$ "
elif [ $1 == "./minishell" ]; then
	wait="MINISHELL$ "
else
	echo "Usage: $0 [bash] or [./minishell]"
	exit 1
fi


# expectコマンドで対話的にテストする
expect -c "

# タイムアウトを10秒に設定
set timeout 10

# 実行ファイルを起動
spawn $run
sleep 0.5

# プロンプトが表示されたらコマンドを送信
expect \"$wait\" { send \"pwd\n\" }
expect \"$wait\" { send \"ls\n\" }
expect \"$wait\" { send \"exit\n\" }
expect eof
"