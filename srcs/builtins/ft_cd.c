/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:48:53 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/12 17:02:04 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	change_dir(t_cmd_info cmd_info, t_env_pair *env_list,
			char *variable_name)
{
	t_env_pair	*env_pair;
	char		*target;

	target = NULL;
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
	return (0);
}

static int	ft_run_cd(t_cmd_info cmd_info, t_env_pair *env_list,
			char *variable_name, char *cwd)
{
	t_env_pair	*tmp;
	char		current_dir[PATH_MAX];

	if (change_dir(cmd_info, env_list, variable_name) == CMD_ERROR)
		return (CMD_ERROR);
	tmp = ft_search_env_node("PWD", env_list);
	if (!tmp)
		tmp = ft_new_env2(ft_strdup("OLDPWD"), NULL);
	else
		tmp = ft_new_env2(ft_strdup("OLDPWD"), ft_strdup(tmp->value));
	ft_update_env_list(&env_list, tmp, 0);
	getcwd(current_dir, PATH_MAX);
	ft_internal_pwd(1);
	tmp = ft_new_env2(ft_strdup("PWD"), ft_strdup(current_dir));
	ft_update_env_list(&env_list, tmp, 0);
	return (0);
}

int	ft_cd(t_cmd_info cmd_info, t_env_info env_info)
{
	int		argc;
	char	cwd[PATH_MAX];

	(void)env_info;
	argc = ft_array_len(cmd_info.cmd_argv);
	if (argc > 2)
	{
		ft_printf_fd(STDERR_FILENO, "cd: too many arguments\n");
		return (CMD_ERROR);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_printf_fd(STDERR_FILENO,
			"cd: error retrieving current directory: "
			"getcwd: cannot access parent directories: %s\n",
			strerror(errno));
		return (0);
	}
	if (!cmd_info.cmd_argv[1])
		return (ft_run_cd(cmd_info, env_info.env_list, "HOME", cwd));
	else if (!*cmd_info.cmd_argv[1])
		return (0);
	else if (strncmp(cmd_info.cmd_argv[1], "-", 2) == 0)
		return (ft_run_cd(cmd_info, env_info.env_list, "OLDPWD", cwd));
	return (ft_run_cd(cmd_info, env_info.env_list, NULL, cwd));
}

// int main(int ac, char **av)
// {
//     char pathname[PATH_MAX];

//     ft_cd(av);
//     getcwd(pathname, PATH_MAX);
//     fft_printf_fd(STDOUT_FILENO, stdout,"現在のファイルパス:%s\n", pathname);
// }