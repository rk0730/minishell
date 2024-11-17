/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:42:53 by rkitao            #+#    #+#             */
/*   Updated: 2024/11/17 17:00:57 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

// エラーなら1を返す
static int	ft_next_cmd_h(char *cmd, int *ip)
{
	char	c;

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
				return (1);
			}
		}
		(*ip)++;
	}
	return (0);
}

static char	*ft_next_cmd(char *cmd, int *ip)
{
	int		start;
	int		tmp;

	start = *ip;
	if (ft_next_cmd_h(cmd, ip) == 1)
		return (NULL);
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
