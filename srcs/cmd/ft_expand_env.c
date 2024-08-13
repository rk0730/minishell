/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:01:46 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/13 23:28:26 by yyamasak         ###   ########.fr       */
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
	while (word[*endp] != '\0' && word[*endp] != ' ' && word[*endp] != '\"' && word[*endp] != '\'' && word[*endp]!= '\n' && word[*endp] != '=' && !(word[*endp] == '$' && *endp != i))
		(*endp)++;
	if (*endp - i == 1)
	{
		printf("in difference is 1\n");
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

static char	*ft_help4(char *word, int i, int end, t_env_info env_info)
{
	char	*tmp;
	char	*tmp1;

	tmp1 = ft_substr(word, i + 1, end - i - 1);
	tmp = ft_search_env(tmp1, env_info.env_list);
	free(tmp1);
	return (tmp);
}

// wordの環境変数を展開した文字列を返す（wordはfreeされる） doubleqouteが1なら"で囲まれているものを展開,0なら"で囲まれているわけではない　$の処理でこのフラグが必要
char	*ft_expand_env(char *word, t_env_info env_info, int is_doublequote)
{
	char	*result;
	char	*tmp;
	int		i;
	int		end;

	result = ft_strdup("");
	i = 0;
	end = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$' && word[i+1] == '?')//環境変数展開でも$?だけ別処理
			tmp = ft_help1(i, &end);
		else if (word[i] == '$' && (word[i+1] == '\0' || word[i+1] == '='))
		{
			tmp = ft_strdup("$");
			end++;
		}
		else if (word[i] == '$')
		{
			tmp = ft_help2(word, i, &end, is_doublequote);
			if (tmp == NULL)
				tmp = ft_help4(word, i, end, env_info);
		}
		else
			tmp = ft_help3(word, i, &end);
		i = end;
		result = ft_join_free(result, tmp);
	}
	free(word);
	return (result);
}
