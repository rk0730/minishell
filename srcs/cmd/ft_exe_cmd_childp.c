/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd_childp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:10:18 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/14 15:15:25 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include <sys/stat.h>

static int	ft_is_directory(char *dir)
{
	struct stat	statbuf;

	if (access(dir, F_OK) == -1)
		return (0);
	if (stat(dir, &statbuf) == -1)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

static void	ft_exec_direct(t_cmd_info cmd_info, char **cmd_env)
{
	if (ft_is_directory(cmd_info.cmd_argv[0]))
	{
		ft_printf_fd(STDERR_FILENO, "%s: Is a directory\n",
			cmd_info.cmd_argv[0]);
		exit(CMD_EXEC_FAILED);
	}
	if (execve(cmd_info.cmd_argv[0], cmd_info.cmd_argv, cmd_env) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", cmd_info.cmd_argv[0],
			strerror(errno));
		if (errno == ENOENT)
			exit(CMD_NOT_FOUND);
		else if (errno == EACCES)
			exit(CMD_EXEC_FAILED);
		exit(CMD_ERROR);
	}
	ft_free_array(cmd_info.cmd_argv);
}

static void	ft_exec_indirect(t_cmd_info cmd_info, char **cmd_env,
		char **path_array, int i)
{
	char	*tmp;
	char	*cmd_path;

	tmp = ft_strjoin(path_array[i], "/");
	cmd_path = ft_strjoin(tmp, cmd_info.cmd_argv[0]);
	free(tmp);
	if (access(cmd_path, X_OK) == 0)
	{
		if (execve(cmd_path, cmd_info.cmd_argv, cmd_env) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "%s: %s\n", cmd_info.cmd_argv[0],
				strerror(errno));
			YYAMASAK("relative_path: %d\n", errno);
			exit(CMD_ERROR);
		}
	}
	free(cmd_path);
}

static void	ft_find_and_exec(t_cmd_info cmd_info, char **cmd_env,
		char **path_array, t_env_info *env_info_p)
{
	int		i;

	i = 0;
	(void)env_info_p;
	if (!path_array[i])
		ft_exec_direct(cmd_info, cmd_env);
	while (path_array[i])
	{
		ft_exec_indirect(cmd_info, cmd_env, path_array, i);
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "%s: command not found\n",
		cmd_info.cmd_argv[0]);
	ft_free_array(cmd_info.cmd_argv);
	exit(CMD_NOT_FOUND);
}

void	ft_exec_cmd_child(t_cmd_info cmd_info, t_env_info *env_info_p,
		int read_pipe, int write_pipe)
{
	char	**path_array;
	char	**cmd_env;

	ft_choose_fd(cmd_info, read_pipe, write_pipe, TRUE);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	path_array = ft_gen_path_array(env_info_p->env_list);
	cmd_env = ft_gen_cmd_env(env_info_p->env_list);
	if (ft_strchr(cmd_info.cmd_argv[0], '/') != NULL)
		ft_exec_direct(cmd_info, cmd_env);
	else
		ft_find_and_exec(cmd_info, cmd_env, path_array, env_info_p);
}
