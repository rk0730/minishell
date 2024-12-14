/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:13:31 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 16:21:52 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

int	_ft_is_redirect(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, ">", 2) == 0 || ft_strncmp(str, "<", 2) == 0
		|| ft_strncmp(str, ">>", 3) == 0 || ft_strncmp(str, "<<", 3) == 0)
		return (1);
	else
		return (0);
}

int	_ft_redirect_err(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if ((tokens[i][0] == '>' || tokens[i][0] == '<')
			&& _ft_is_redirect(tokens[i]) == 0)
		{
			ft_printf_fd(STDERR_FILENO,
				"syntax error\n");
			return (1);
		}
		if (_ft_is_redirect(tokens[i]))
		{
			if (tokens[i + 1] == NULL || _ft_is_redirect(tokens[i + 1]))
			{
				ft_printf_fd(STDERR_FILENO,
					"syntax error\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	_ft_is_last_redirect(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	i--;
	if (_ft_is_redirect(tokens[i]))
		return (1);
	else
		return (0);
}
