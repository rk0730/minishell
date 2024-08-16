/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:01:46 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/02 16:29:38 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static char	*ft_help1(int i, int *endp)
{
	*endp = i + 2;
	return (ft_itoa(ft_status_code(0, 0)));
}

static char	*ft_help2(char *word, int i, int *endp, int is_doublequote)
{
	*endp = i;
	while (word[*endp] != '\0' && word[*endp] != ' ' && word[*endp] != '\"' && word[*endp] != '\'' && word[*endp]!= '\n')
		(*endp)++;
	if (*endp - i == 1)
	{
		if (is_doublequote == 1)
			return (ft_strdup("$"));
		else
			return (ft_strdup(""));//""で囲まれているわけではなく、$の後ろに何もない場合は何も返さない
	}
	else
		return (NULL);
}

static char	*ft_help3(char *word, int i, int *endp)
{
	*endp = i;
	while (word[*endp] != '\0' && word[*endp] != '$')
		(*endp)++;
	return (ft_substr(word, i, *endp - i));
}

static char	*ft_help4(int *ip, int end, char **old_p, char **tmp_p)
{
	char	*result;

	*ip = end;
	result = ft_strjoin(*old_p, *tmp_p);
	free(*old_p);
	free(*tmp_p);
	return (result);
}

// strの環境変数を展開した文字列を返す doubleqouteが1なら"で囲まれているものを展開,0なら"で囲まれているわけではない　$の処理でこのフラグが必要
char	*ft_expand_env(char *word, t_env_info env_info, int is_doublequote)
{
	char	*result;
	char	*tmp;
	// char	*before;
	int		i;
	int		end;

	result = ft_strdup("");
	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$' && word[i+1] == '?')//環境変数展開でも$?だけ別処理
			tmp = ft_help1(i, &end);
		else if (word[i] == '$')
		{
			tmp = ft_help2(word, i, &end, is_doublequote);
			if (tmp == NULL)
				tmp = ft_search_env(ft_substr(word, i + 1, end - i - 1), env_info.env_list);
		}
		else
			tmp = ft_help3(word, i, &end);
		result = ft_help4(&i, end, &result, &tmp);
	}
	return (result);
}
