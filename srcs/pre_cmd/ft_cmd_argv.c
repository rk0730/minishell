/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:12:46 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 18:55:33 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static char	*_ft_help1(char *str, int i, int *endp, t_env_info env_info)
{
	char	*tmp;
	char	*result;

	if (str[i] == '\"')
	{
		*endp = i + 1;
		while (str[*endp] != '\0' && str[*endp] != '\"')
			(*endp)++;
		(*endp)++;
		tmp = ft_substr(str, i + 1, *endp - i - 2);
		result = _ft_expand_env(tmp, env_info, 1);
		return (result);
	}
	else if (str[i] == '\'')
	{
		*endp = i + 1;
		while (str[*endp] != '\0' && str[*endp] != '\'')
			(*endp)++;
		(*endp)++;
		return (ft_substr(str, i + 1, *endp - i - 2));
	}
	ft_printf_fd(STDERR_FILENO, "error in ft_tokenize _ft_help1\n");
	return (NULL);
}

char	*_ft_expand_normal(char *str, int i, int *endp, t_env_info env_info)
{
	char	*tmp;
	char	*result;

	*endp = i;
	while (str[*endp] != '\0' && str[*endp] != '\"' && str[*endp] != '\'')
		(*endp)++;
	if (str[*endp - 1] == '$' && (str[*endp] == '\'' || str[*endp] == '\"'))
		tmp = ft_substr(str, i, *endp - i - 1);
	else
		tmp = ft_substr(str, i, *endp - i);
	result = _ft_expand_env(tmp, env_info, 0);
	return (result);
}

char	*_ft_tokenize(char *str, t_env_info env_info)
{
	char	*result;
	char	*tmp;
	int		i;
	int		end;

	result = ft_strdup("");
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			tmp = _ft_help1(str, i, &end, env_info);
		else
			tmp = _ft_expand_normal(str, i, &end, env_info);
		i = end;
		result = ft_join_free(result, tmp);
	}
	return (result);
}

char	**_ft_gen_cmd_argv(char **tokens, t_env_info env_info)
{
	char	**cmd_argv;
	int		i;

	i = 0;
	cmd_argv = (char **)malloc(sizeof(char *));
	if (!cmd_argv)
		return (NULL);
	cmd_argv[0] = NULL;
	while (tokens[i])
	{
		if (_ft_is_redirect(tokens[i]))
		{
			i += 2;
			continue ;
		}
		cmd_argv = _ft_one_token(tokens[i], cmd_argv, env_info);
		i++;
	}
	return (cmd_argv);
}
