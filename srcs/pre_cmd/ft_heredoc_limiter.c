/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_limiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:29:02 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 16:32:09 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static char	*_ft_get_token(int *end, char *str, int i)
{
	char	*tmp;

	if (str[i] == '\"' || str[i] == '\'')
	{
		*end = i + 1;
		while (str[*end] != '\0' && str[*end] != str[i])
			(*end)++;
		tmp = ft_substr(str, i + 1, (*end) - i - 1);
		(*end)++;
	}
	else
	{
		*end = i;
		while (str[*end] != '\0' && str[*end] != '\"' && str[*end] != '\'')
			(*end)++;
		tmp = ft_substr(str, i, (*end) - i);
	}
	return (tmp);
}

char	*_ft_limit_tokenize(char *str, int *is_quote)
{
	char	*result;
	char	*tmp;
	char	*before;
	int		i;
	int		end;

	result = ft_strdup("");
	i = 0;
	*is_quote = 0;
	while (str[i] != '\0')
	{
		tmp = _ft_get_token(&end, str, i);
		before = result;
		result = ft_strjoin(before, tmp);
		free(before);
		free(tmp);
		i = end;
	}
	if (ft_strchr(str, '\'') != NULL || ft_strchr(str, '\"') != NULL)
		*is_quote = 1;
	return (result);
}
