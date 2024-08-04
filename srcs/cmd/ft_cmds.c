/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:42:53 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/04 19:28:09 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static char	*ft_next_cmd(char *cmd, int *ip)
{
	int		start;
	int		tmp;
	char	c;

	start = *ip;
	while (cmd[*ip] && cmd[*ip] != '|')
	{
		if (cmd[*ip] == '\'' || cmd[*ip] == '\"')
		{
			c = cmd[*ip];
			(*ip)++;
			while (cmd[*ip] != '\0' && cmd[*ip] != c)
				(*ip)++;
			if (cmd[*ip] == '\0')
			{
				ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
				return (NULL);
			}
		}
		(*ip)++;
	}
	//すべてスペースでないか確認する
	tmp = start;
	while (cmd[tmp] && cmd[tmp] == ' ')
		tmp++;
	if (tmp == *ip)
	{
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `|'\n");
		return (NULL);
	}
	else
		return (ft_substr(cmd, start, *ip - start));
}

// |で分割する。クォーテーションエラーと| |のエラーも確認する
char	**ft_gen_cmds(char *cmd)
{
	char	**cmd_argv;
	char	*tmp;
	int		i;

	cmd_argv = (char **)malloc(sizeof(char *));
	if (!cmd_argv)
		exit(EXIT_FAILURE);
	cmd_argv[0] = NULL;
	i = 0;
	while (cmd[i])
	{
		tmp = ft_next_cmd(cmd, &i);
		if (tmp == NULL)
		{
			ft_free_array(cmd_argv);
			return (NULL);
		}
		else
		{
			cmd_argv = ft_add_str(cmd_argv, tmp);
		}
		if (cmd[i] == '|')
			i++;
	}
	return (cmd_argv);
}
