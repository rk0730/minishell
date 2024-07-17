/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:44:39 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/07/17 22:40:44 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// strの環境変数を展開した文字列を返す
static char	*ft_expand_env(char *str, t_env_pair *env_list)
{
	char	*result;
	char	*tmp;
	char	*before;
	int		i;
	int		end;

	result = ft_strdup("");
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (str[i+1] == '\"' || str[i+1] == '\'')
			{
				i++;
				continue ;
			}
			end = i;
			while (str[end] != '\0' && str[end] != ' ' && str[end] != '\"' && str[end] != '\'')
				end++;
			tmp = ft_search_env(ft_substr(str, i + 1, end - i - 1), env_list);
		}
		else
		{
			end = i;
			while (str[end] != '\0' && str[end] != '$')
				end++;
			tmp = ft_substr(str, i, end - i);
		}
		before = result;
		result = ft_strjoin(before, tmp);
		free(before);
		free(tmp);
		i = end;
	}
	return (result);
}


// tokenの各文字列が"で挟まれていたら環境変数展開したり、'で挟まれていたらそれを除く（リダイレクトは飛ばす）
char	**ft_gen_cmd_array(char **tokens, t_env_pair *env_list)
{
	char	**cmd_array;
	int		i;

	i = 0;
	cmd_array = (char **)malloc(sizeof(char *) * (ft_array_len(tokens) + 1));
	if (!cmd_array)
		return (NULL);
	while (tokens[i])
	{
		cmd_array[i] = ft_expand_env(tokens[i], env_list);
		i++;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}
