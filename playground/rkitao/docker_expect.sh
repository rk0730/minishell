chmod 000 ../../minishell-tester/no_permission
chmod 444 ../../minishell-tester/no_write_permission
chmod 222 ../../minishell-tester/no_read_permission;
docker container exec my-ubuntu bash -c "cd /home/rkitao/42/minishell/minishell-tester && ./expect.sh bash '~/42/minishell/minishell-tester$ '"
chmod 644 ../../minishell-tester/no_permission
chmod 644 ../../minishell-tester/no_write_permission
chmod 644 ../../minishell-tester/no_read_permission