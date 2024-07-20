#!/bin/bash

ERR1=$(cat err1)
ERR2=$(cat err2)

# エラーメッセージの整形（各行:で分割し、3番目以降のフィールドを取得）
# ERR2=$(echo "$ERR2" | cut -d':' -f3- | sed 's/^ //')

# ERR1の各行がERR2の各行に含まれているか確認する
is_err_same=true
# ERR1=(${ERR1//\n/ })
# ERR2=(${ERR2//\n/ })
IFS=\n ARRAY1=(${ERR1})
IFS=\n ARRAY2=(${ERR2})
for i in ${!ARRAY1[@]}; do
	printf "${ARRAY1[$i]}--- & ${ARRAY2[$i]}---\n"  
	if [[ "$ERR2" != *"$ERR1" ]]; then
		is_err_same=false
		break
	fi
done

for S in "${ARR[@]}"; do echo "$S"; done

if $is_err_same; then
	printf "✓\n"
else
	printf "✗\n"
fi