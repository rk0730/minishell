#!/bin/bash

declare commands
declare stdout_file
declare stderr_file

commands='echo test'
stdout_file=$(mktemp)
stderr_file=$(mktemp)

# printf "%b" "$commands" | ../minishell > $stdout_file 2> $stderr_file
printf "%b" "$commands" | ../minishell > $stdout_file 2> $stderr_file
# echo > test2 "d	ef" && cat test1 > test3 test2 && cat test3 && cat test2 && exit