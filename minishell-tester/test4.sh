source ./test_utils.sh

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	start_test
fi

# テスト4 必ず最後にexitを入れる

# exitテスト
exec_test 'pwd' 'exit 42'
exec_test 'pwd' 'exit 1 2'
exec_test 'pwd' 'exit 2147483647'
exec_test 'pwd' 'exit 2147483648'
exec_test 'pwd' 'exit 2147483649'
exec_test 'pwd' 'exit -2147483646'
exec_test 'pwd' 'exit -2147483647'
exec_test 'pwd' 'exit -2147483648'
exec_test 'pwd' 'exit -2147483649'
exec_test 'pwd' 'exit 4294967295'
exec_test 'pwd' 'exit 4294967296'
exec_test 'pwd' 'exit 4294967297'
exec_test 'pwd' 'exit 4294967298'
exec_test 'pwd' 'exit -4294967296'
exec_test 'pwd' 'exit -4294967297'
exec_test 'pwd' 'exit -4294967298'
exec_test 'pwd' 'exit -4294967299'
exec_test 'pwd' 'exit 123456789123456789'
exec_test 'pwd' 'exit 987654321987654321'
exec_test 'pwd' 'exit 9223372036854775807'
exec_test 'pwd' 'exit 9223372036854775808'
exec_test 'pwd' 'exit 9223372036854775809'
exec_test 'pwd' 'exit -9223372036854775807'
exec_test 'pwd' 'exit -9223372036854775808'
exec_test 'pwd' 'exit -9223372036854775809'
exec_test 'pwd' 'exit -9223372036854775810'
exec_test 'pwd' 'exit '
exec_test 'pwd' 'exit 0'
exec_test 'pwd' 'exit -0'
exec_test 'pwd' 'exit +0'
exec_test 'pwd' 'exit 254'
exec_test 'pwd' 'exit 255'
exec_test 'pwd' 'exit 256'
exec_test 'pwd' 'exit 257'
exec_test 'pwd' 'exit -1'
exec_test 'pwd' 'exit -10'
exec_test 'pwd' 'exit +10'
exec_test 'pwd' 'exit -42'
exec_test 'pwd' 'exit --10'
exec_test 'pwd' 'exit --10 1'
exec_test 'pwd' 'exit ++10 1'
exec_test 'pwd' 'exit ++10'
exec_test 'pwd' 'exit "  42   "'
exec_test 'pwd' 'exit "  1""2""3"'
exec_test 'pwd' 'exit "   """"1""2""""3""   ""   "'
exec_test 'pwd' 'exit "  1  3 "' 'echo $?' 'exit'
exec_test 'pwd' 'exit +'
exec_test 'pwd' 'exit ++'
exec_test 'pwd' 'exit -'
exec_test 'exit 24 | exit 42' 'echo $?' 'exit'
exec_test 'exit 1 2 | exit 42' 'echo $?' 'exit'
exec_test 'exit 42 | exit 1 2' 'echo $?' 'exit'
exec_test 'exit 1 2 | exit 42 | exit 3 4' 'echo $?' 'exit'
exec_test 'exit | exit' 'exit'

if [ "${BASH_SOURCE[0]}" == "$0" ]; then
	end_test
fi