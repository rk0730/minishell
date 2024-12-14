/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiguous_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:54:42 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 18:20:19 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static int	_ft_help(char *file_name, int *ip, int *endp, t_env_info env_info)
{
	char	*expanded;
	char	*tmp;

	expanded = _ft_expand_normal(file_name, *ip, endp, env_info);
	RKITAO("expanded: %s\n", expanded);
	tmp = expanded;
	while (*tmp)
	{
		if (ft_isspace(*tmp) == 1)
		{
			free(expanded);
			return (1);
		}
		tmp++;
	}
	free(expanded);
	*ip = *endp;
	return (0);
}

int	_ft_is_ambiguous_redirect(char *file_name, t_env_info env_info)
{
	int		i;
	int		end;

	i = 0;
	while (file_name[i])
	{
		if (file_name[i] == '\"' || file_name[i] == '\'')
		{
			end = i + 1;
			while (file_name[end] != '\0' && file_name[end] != file_name[i])
				end++;
			if (file_name[end] == '\0')
				ft_printf_fd(STDOUT_FILENO,
					"bug in _ft_is_ambiguous_redirect\n");
			i = end + 1;
		}
		else
		{
			if (_ft_help(file_name, &i, &end, env_info) == 1)
				return (1);
		}
	}
	return (0);
}
