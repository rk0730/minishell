/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:48:53 by yyamasak          #+#    #+#             */
/*   Updated: 2024/10/28 13:36:11 by yyamasak         ###   ########.fr       */
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
int	ft_cd(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe)
{
	int		argc;
	char	*dir_name;

	(void)env_info;
	ft_choose_fd(cmd_info, read_pipe, write_pipe);
	argc = ft_array_len(cmd_info.cmd_argv);
	if (argc < 2)
		return (0);
	dir_name = cmd_info.cmd_argv[1];
	if (argc > 2)
	{
		ft_printf_fd(STDERR_FILENO, "cd: too many arguments\n");
		return (CMD_ERROR);
	}
	else if (chdir(dir_name) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: %s\n", dir_name, strerror(errno));
		return (CMD_ERROR);
	}
	// ft_printf_fd(STDERR_FILENO, "error in ft_cd\n");
	return (CMD_ERROR);
}

// int main(int ac, char **av)
// {
//     char pathname[PATH_MAX];

//     ft_cd(av);
//     getcwd(pathname, PATH_MAX);
//     fprintf(stdout,"現在のファイルパス:%s\n", pathname);
// }