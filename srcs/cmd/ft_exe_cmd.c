/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:05:08 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/07/16 17:56:57 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void	ft_find_and_exec(char **cmd_array, char **path_array)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	while (path_array[i])
	{
		tmp = ft_strjoin(path_array[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_array[0]);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
		{
			if (execve(cmd_path, cmd_array, NULL) == -1)
				exit(CMD_ERROR);
		}
		free(cmd_path);
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "%s: command not found\n", cmd_array[0]);
	ft_free_array(cmd_array);
	exit(CMD_NOT_FOUND);
}

static void	ft_exec_direct(char **cmd_array)
{
	if (execve(cmd_array[0], cmd_array, NULL) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", cmd_array[0], strerror(errno));
		exit(CMD_ERROR);
	}
	ft_free_array(cmd_array);
}

// コマンドを実行する関数、これを呼んだプロセスはexitされる
void	ft_exec_cmd(char *cmd, t_env_pair *env_list)
{
	char	**cmd_array;
	char	**tokens;
	char	**path_array;
	
	// cmd_array = ft_gen_tokens(cmd);//ft_gen_cmd_array()に変える！
	tokens = ft_gen_tokens(cmd);
	cmd_array = ft_gen_cmd_array(tokens, env_list);
	path_array = ft_gen_path_array(env_list);
	if (ft_strchr(cmd, '/') != NULL)
		ft_exec_direct(cmd_array);
	else
		ft_find_and_exec(cmd_array, path_array);
}
