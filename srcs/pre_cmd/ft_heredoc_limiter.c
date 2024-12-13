/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_limiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:29:02 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/13 11:29:35 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

// クォーテーションエラーがあった際はNULLを返すように作ったが、最初にクォーテーションはチェックしているため、ここでそのエラーが出ることはなさそう
// limiterを求める関数、"や'で囲まれているものはそのまま返す、 is_quoteはheredoc中に打ち込まれるものを展開する際の場合分けのflagになる
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
		if (str[i] == '\"' || str[i] == '\'')
		{
			end = i + 1;
			while (str[end] != '\0' && str[end] != str[i])
				end++;
			//　クォーテーションエラーはおそらく起き得ないので削除
			// if (str[end] == '\0')
			// {
			// 	free(result);
			// 	return (NULL);
			// }
			tmp = ft_substr(str, i + 1, end - i - 1);
			end++;
		}
		else
		{
			end = i;
			while (str[end] != '\0' && str[end] != '\"' && str[end] != '\'')
				end++;
			tmp = ft_substr(str, i, end - i);
		}
		before = result;
		result = ft_strjoin(before, tmp);
		free(before);
		free(tmp);
		i = end;
	}
	// limiterにクォーテーションがあるか確認
	if (ft_strchr(str, '\'') != NULL || ft_strchr(str, '\"') != NULL)
		*is_quote = 1;
	return (result);
}
