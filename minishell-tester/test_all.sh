#!/bin/bash


# ./test_utils.sh $*
source ./test_utils.sh
start_test

# 連番のtestスクリプトを順番にsourceする
tmp=1  # ループのカウンタ
while true; do
	file_name="test${tmp}.sh"

	# ファイルが存在するか確認
	if [ -f "$file_name" ]; then
		source "./$file_name"
	else
		echo "$file_name does not exist."
		break
	fi

	# 次の番号へ
	tmp=$((tmp + 1))
done

end_test