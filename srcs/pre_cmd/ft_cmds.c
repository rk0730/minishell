/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:42:53 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 17:53:21 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static int	_ft_next_cmd_h(char *cmd, int *ip)
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
				ft_printf_fd(STDERR_FILENO,
					"syntax error near unexpected token `newline'\n");
				return (1);
			}
		}
		(*ip)++;
	}
	return (0);
}

static char	*_ft_next_cmd(char *cmd, int *ip)
{
	int	start;
	int	tmp;

	start = *ip;
	if (_ft_next_cmd_h(cmd, ip) == 1)
		return (NULL);
	tmp = start;
	while (cmd[tmp] && ft_isspace(cmd[tmp]))
		tmp++;
	if (tmp == *ip)
	{
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `|'\n");
		return (NULL);
	}
	else
		return (ft_substr(cmd, start, *ip - start));
}

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
		tmp = _ft_next_cmd(cmd, &i);
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
