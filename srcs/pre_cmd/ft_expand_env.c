/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:01:46 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 18:14:43 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static char	*_ft_help1(int i, int *endp)
{
	*endp = i + 2;
	return (ft_itoa(ft_status_code(0, 0)));
}

static char	*_ft_help3(char *word, int i, int *endp)
{
	*endp = i;
	while (word[*endp] != '\0' && word[*endp] != '$')
		(*endp)++;
	return (ft_substr(word, i, *endp - i));
}

static char	*_ft_help4(char *word, int i, int end, t_env_info env_info)
{
	char	*tmp;
	char	*tmp1;

	tmp1 = ft_substr(word, i + 1, end - i - 1);
	tmp = ft_search_env(tmp1, env_info.env_list);
	free(tmp1);
	return (tmp);
}

static char	*_ft_expand_dollar(char *word, int *ip, int *endp,
		t_env_info env_info)
{
	char	*result;

	if (word[*ip] == '$' && word[*ip + 1] == '?')
		result = _ft_help1(*ip, endp);
	else if (word[*ip] == '$' && ft_isdigit(word[*ip + 1]))
	{
		*endp += 2;
		result = ft_strdup("");
	}
	else if (word[*ip] == '$'
		&& (!ft_isalpha(word[*ip + 1]) && word[*ip + 1] != '_'))
	{
		result = ft_strdup("$");
		*endp += 1;
	}
	else
	{
		*endp += 2;
		while (ft_isalnum(word[*endp]) || word[*endp] == '_')
			(*endp)++;
		result = _ft_help4(word, *ip, *endp, env_info);
	}
	return (result);
}

char	*_ft_expand_env(char *word, t_env_info env_info, int is_doublequote)
{
	char	*result;
	char	*tmp;
	int		i;
	int		end;

	result = ft_strdup("");
	i = 0;
	end = 0;
	(void)is_doublequote;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
			tmp = _ft_expand_dollar(word, &i, &end, env_info);
		else
			tmp = _ft_help3(word, i, &end);
		i = end;
		result = ft_join_free(result, tmp);
	}
	free(word);
	return (result);
}
