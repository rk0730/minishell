source ./val.sh

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
    echo "このスクリプトは直接実行されました"
else
    echo "このスクリプトは他のファイルから source されています"
fi

say_hello() {
	echo "Hello"
	test_val=1
}

echo $test_val