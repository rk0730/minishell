/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:48:53 by yyamasak          #+#    #+#             */
/*   Updated: 2024/11/24 14:26:36 by yyamasak         ###   ########.fr       */
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
static int ft_run_cd(t_cmd_info cmd_info, t_env_pair *env_list, char *variable_name, char *cwd)
{
	t_env_pair	*env_pair;
	t_env_pair	*tmp;
	char		*target;

	if (!variable_name) 
		target = cmd_info.cmd_argv[1];
	else 
	{
		env_pair = ft_search_env_node(variable_name, env_list);
		if (!env_pair)
		{
			ft_printf_fd(STDERR_FILENO, "cd: %s not set\n", variable_name);
			return (CMD_ERROR);
		}
		target = env_pair->value;
	}
	if (chdir(target) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: %s\n", target, strerror(errno));
		return (CMD_ERROR);
	}
	tmp = ft_new_env2(ft_strdup("OLDPWD"), ft_strdup(cwd));
	ft_update_env_list(&env_list, tmp, 0);
	return (0);
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
	{
		ft_printf_fd(STDERR_FILENO, "cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n", strerror(errno));
		return (0);
	}
	if (!cmd_info.cmd_argv[1])
		return (ft_run_cd(cmd_info, env_info.env_list, "HOME", cwd));
	else if (strncmp(cmd_info.cmd_argv[1], "-", 2) == 0)
		return (ft_run_cd(cmd_info, env_info.env_list, "OLDPWD", cwd));
	return (ft_run_cd(cmd_info, env_info.env_list, NULL, cwd));
}

// int main(int ac, char **av)
// {
//     char pathname[PATH_MAX];

//     ft_cd(av);
//     getcwd(pathname, PATH_MAX);
//     fprintf(stdout,"現在のファイルパス:%s\n", pathname);
// }