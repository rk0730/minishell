/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:48:53 by yyamasak          #+#    #+#             */
/*   Updated: 2024/11/21 15:35:02 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <linux/limits.h>
// #include <stdio.h>
// #include <errno.h>
// #include <sys/stat.h>
// #include <string.h>
# include "builtins.h"

// static  int count_args(char **argv)
// {
//     int num;

//     num = 0;
//     while (argv[num])
//         num++;
//     return (num);
// }

// {cd PATH}で動くが{cd}のみで来た場合は動かさない方針で 終了ステータスを返す

// TODO add logic
// TODO add directory change
// TODO add PWD, OLDPWD variable updating
// TODO add error message
static int ft_run_cd(t_cmd_info cmd_info, int mode, char *variable_name)
{
	if (!cmd_info.cmd_argv[1])
	{
		ft_printf_fd(STDERR_FILENO, "this is moving to HOME\n");
		return (0);
	}
	if (strncmp(cmd_info.cmd_argv[1], "-", 2) == 0)
		return 0;
	if (chdir(cmd_info.cmd_argv[1]) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: %s\n", cmd_info.cmd_argv[1], strerror(errno));
		return (CMD_ERROR);
	}
}
int	ft_cd(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe)
{
	int		argc;
    char	cwd[PATH_MAX];

	(void)env_info;
	ft_choose_fd(cmd_info, read_pipe, write_pipe, FALSE);
	argc = ft_array_len(cmd_info.cmd_argv);
	if (argc > 2)
	{
		ft_printf_fd(STDERR_FILENO, "cd: too many arguments\n");
		return (CMD_ERROR);
	}
	if (getcwd(cwd, PATH_MAX) == NULL) 
		ft_printf_fd(STDERR_FILENO, "cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n", strerror(errno));
	if (!cmd_info.cmd_argv[1])
		return (ft_run_cd(cmd_info, 0, "HOME"));
	else if (strncmp(cmd_info.cmd_argv[1], "-", 2) == 0)
		return (ft_run_cd(cmd_info, 0, "OLDPWD"));
	return (ft_run_cd(cmd_info, 1, ""));
	// if (chdir(cmd_info.cmd_argv[1]) == -1)
	// {
	// 	ft_printf_fd(STDERR_FILENO, "cd: %s: %s\n", cmd_info.cmd_argv[1], strerror(errno));
	// 	return (CMD_ERROR);
	// }
	return (0);
}

// int main(int ac, char **av)
// {
//     char pathname[PATH_MAX];

//     ft_cd(av);
//     getcwd(pathname, PATH_MAX);
//     fprintf(stdout,"現在のファイルパス:%s\n", pathname);
// }