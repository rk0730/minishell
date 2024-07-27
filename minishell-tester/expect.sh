#!/bin/bash

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

# 引数の数が2でない場合はエラーを出力して終了
if [ $# -ne 2 ]; then
	echo "Usage: $0 <bash or ./minishell> <\"$ \" or \"# \" or \"MINISHELL$ \">"
	exit 1
fi

run=$1
wait=$2

# 引数がbashかminishellかでwait変数（プロンプト）の値を変える
# if [ $1 == "bash" ]; then
# 	wait="bash-$(bash --version | head -n 1 | awk '{split($4, version, "."); print version[1] "." version[2]}')$ "
# 	rum="bash"
# 	printf "\n$BOLDMAGENTA%s$RESET\n\n" "bash"
# elif [ $1 == "minishell" ]; then
# 	# minishellをビルド
# 	wait="MINISHELL$ "
# 	run="./minishell"
# 	make -C .. all
# 	make -C .. clean
# 	cp ../minishell .
# 	chmod 755 minishell
# 	printf "\n$BOLDMAGENTA%s$RESET\n\n" "minishell"
# else
# 	echo "Usage: $0 bash or minishell"
# 	exit 1
# fi

# minishellをビルド
if [ $1 == "./minishell" ]; then
	rm -f minishell
	make -C .. re > /dev/null
	make -C .. clean > /dev/null
	cp ../minishell .
	chmod 755 minishell
fi

printf "$BOLDMAGENTA run: %s$RESET\n" "$run"
printf "$BOLDMAGENTA wait: %s$RESET\n" "$wait"

# 権限の変更
chmod 000 no_permission
chmod 444 no_write_permission
chmod 222 no_read_permission

# expectコマンドで対話的にテストする
# エラーの挙動やheredocの挙動はこれで確認できる
expect -c "

# タイムアウトを10秒に設定
set timeout 15

# 実行ファイルを起動
spawn $run
sleep 0.5

# プロンプトが表示されたらコマンドを送信

expect \"$wait\" { sleep 0.02; send \"lsl\n\" }

expect \"$wait\" { send \"cat no_permission\n\" }

expect \"$wait\" { send \"cat << EOF\n\" }
expect \"> \" { send \"test\n\" }
expect \"> \" { send \"EOF\n\" }

expect \"$wait\" { send \"<< EOF << eof << eee cat\n\" }
expect \"> \" { sleep 0.02; send \"test1\n\" }
expect \"> \" { sleep 0.02; send \"eof\n\" }
expect \"> \" { sleep 0.02; send \"test2\n\" }
expect \"> \" { sleep 0.02; send \"eee\n\" }
expect \"> \" { sleep 0.02; send \"test3\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }
expect \"> \" { sleep 0.02; send \"test4\n\" }
expect \"> \" { sleep 0.02; send \"eof\n\" }
expect \"> \" { sleep 0.02; send \"test5\n\" }
expect \"> \" { sleep 0.02; send \"test6\n\" }
expect \"> \" { sleep 0.02; send \"eee\n\" }

expect \"$wait\" { send \"echo 'test file' > file\n\" }
expect \"$wait\" { send \"cat << EOF < file\n\" }
expect \"> \" { sleep 0.02; send \"test\n\" }
expect \"> \" { sleep 0.02; send \"123\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }
expect \"$wait\" { send \"rm file\n\" }

expect \"$wait\" { send \"cat <<eof | cat << EOF\n\" }
expect \"> \" { sleep 0.02; send \"test1\n\" }
expect \"> \" { sleep 0.02; send \"eof\n\" }
expect \"> \" { sleep 0.02; send \"test2\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }

expect \"$wait\" { send \"cat << EOF >\n\" }
expect \"> \" { sleep 0.02; send \"test1\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }

expect \"$wait\" { send \"cat <<<< EOF\n\" }

expect \"$wait\" { send \"cat << EOF >>>> out\n\" }

expect \"$wait\" { send \"cat << EOF >\n\" }
expect \"> \" { sleep 0.02; send \"test\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }

expect \"$wait\" { send \"cat << EOF <\n\" }
expect \"> \" { sleep 0.02; send \"test\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }

expect \"$wait\" { send \"cat << EOF <<<<\n\" }

expect \"$wait\" { send \"cat << EOF > < no_write_permission\n\" }

expect \"$wait\" { send \"<no_such_file ls|lsl|ls \\\"|\\\"|ls|>\\\"|\\\" cat' 'ls' 'cat \\\"|\\\"' 'rm \\\"|\\\"\n\" }
expect \"$wait\" { send \"ls\n\" }
expect \"$wait\" { send \"cat \\\"|\\\"\n\" }
expect \"$wait\" { send \"rm \\\"|\\\"\n\" }

expect \"$wait\" { sleep 0.02; send \"cat << EOF > <\n\" }

expect \"$wait\" { send \"cat > no_write_permission <<\n\" }

expect \"$wait\" { send \"cat > no_write_permission << EOF <<\n\" }
expect \"> \" { sleep 0.02; send \"test\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }

expect \"$wait\" { send \"time sleep 2 | sleep 2 | sleep 2\n\" }

expect \"$wait\" { send \"time < no_such_file sleep 3 | sleep 1\n\" }

expect \"$wait\" { send \"cat hello.c | wc -cl\n\" }

expect \"$wait\" { send \"cat << EOF | ls\n\" }
expect \"> \" { sleep 0.02; send \"test\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }

expect \"$wait\" { send \"cat < no_permission | < no_read_permission cat | cat << EOF |cat|cat|cat\n\" }
expect \"> \" { sleep 0.02; send \"test\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }

expect \"$wait\" { send \"cat << EOF | cat << EOF | cat << EOF | cat << EOF|cat\n\" }
expect \"> \" { sleep 0.02; send \"1\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }
expect \"> \" { sleep 0.02; send \"2\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }
expect \"> \" { sleep 0.02; send \"3\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }
expect \"> \" { sleep 0.02; send \"4\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }

expect \"$wait\" { send \"cat <no_\\\"read\\\"_permission > no_write_\\\"permission\\\"\\\"\\\" | ls | cat <<EOF | cat< no_permission|ls|cat<<eof\n\" }
expect \"> \" { sleep 0.02; send \"TEST\n\" }
expect \"> \" { sleep 0.02; send \"EOF\n\" }
expect \"> \" { sleep 0.02; send \"test\n\" }
expect \"> \" { sleep 0.02; send \"eof\n\" }

expect \"$wait\" { send \"ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls\n\" }

expect \"$wait\" { send \"ls | | ls\n\" }

expect \"$wait\" { send \"exit\n\" }
expect eof
"

# 権限を戻す
chmod 644 no_permission
chmod 644 no_write_permission
chmod 644 no_read_permission

rm -f minishell