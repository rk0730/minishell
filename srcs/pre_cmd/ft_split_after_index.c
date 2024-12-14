/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_after_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:35:17 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 18:57:00 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static size_t	ft_count_words(char const *s)
{
	size_t	count;
	size_t	start;
	size_t	end;

	if (!s)
		return (0);
	start = 0;
	count = 0;
	while (s[start])
	{
		while (s[start] && ft_isspace(s[start]))
			start = start + 1;
		end = start;
		while (s[end] && !ft_isspace(s[end]))
			end = end + 1;
		if (end > start)
			count++;
		start = end;
	}
	return (count);
}

static void	ft_check_free(char ***result_p, size_t count)
{
	if ((*result_p)[count] != NULL)
		return ;
	while (count > 0)
	{
		count--;
		free((*result_p)[count]);
	}
	free(*result_p);
	*result_p = NULL;
}

static void	ft_help(char ***result_p, char const *s)
{
	size_t	start;
	size_t	end;
	size_t	count;

	start = 0;
	count = 0;
	while (s[start])
	{
		while (s[start] && ft_isspace(s[start]))
			start++;
		end = start;
		while (s[end] && !ft_isspace(s[end]))
			end++;
		if (end <= start)
			continue ;
		(*result_p)[count] = ft_substr(s, (unsigned int)start, end - start);
		ft_check_free(result_p, count);
		if (!(*result_p))
			return ;
		start = end;
		count++;
	}
}

static char	**_ft_split_isspace(char *s)
{
	size_t	words;
	char	**result;

	if (!s)
		return (NULL);
	words = ft_count_words(s);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	result[words] = NULL;
	ft_help(&result, s);
	if (!result)
		return (NULL);
	return (result);
}

char	**_ft_split_after_index(char *str, int split_index)
{
	char	**array;

	array = _ft_split_isspace(str + split_index);
	if (array[0] != NULL)
		array[0] = ft_join_free(ft_substr(str, 0, split_index), array[0]);
	else if (ft_strlen(str) > 0)
	{
		free(array);
		array = (char **)malloc(sizeof(char *) * 2);
		array[0] = ft_substr(str, 0, split_index);
		array[1] = NULL;
	}
	return (array);
}
