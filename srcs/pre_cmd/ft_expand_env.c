/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:01:46 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 14:50:52 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static char	*_ft_help1(int i, int *endp)
{
	*endp = i + 2;
	return (ft_itoa(ft_status_code(0, 0)));
}

// static char	*ft_help2(char *word, int i, int *endp, int is_doublequote)
// {
// 	*endp = i;
// 	while (word[*endp] != '\0' && word[*endp] != ' ' 
//	&& word[*endp] != '\"' && word[*endp] != '\''
//	&& word[*endp]!= '\n' && word[*endp] != '='
//	&& !(word[*endp] == '$' && *endp != i))
// 		(*endp)++;
// 	if (*endp - i == 1)
// 	{
// 		if (is_doublequote == 1)
// 			return (ft_strdup("$"));
// 		else
// 			return (ft_strdup(""));//""で囲まれているわけではなく、$の後ろに何もない場合は何も返さない
// 	}
// 	else
// 		return (NULL);
// }

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

// $の展開ルール（tokenizeの方で$""とS''だけ処理している）
// 環境変数とは英字またはアンダースコアで始まり、英数字またはアンダースコアで構成される文字列
// $（数字）ならその2文字を無視する
// $(英数字とアンダースコア以外（ヌル文字も含む）)ならそのまま表示する

// wordの環境変数を展開した文字列を返す（wordはfreeされる） 
// doublequoteをフラグに使っていたが、おそらくいらなくなった
// 一応引数には残している
// （doubleqouteが1なら"で囲まれているものを展開,0なら"で囲まれているわけではない　$の処理でこのフラグが必要）
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
		{
			// $の処理
			// 環境変数展開でも$?だけ別処理
			if (word[i] == '$' && word[i + 1] == '?')
				tmp = _ft_help1(i, &end);
			else if (word[i] == '$' && ft_isdigit(word[i + 1]))
			{
				// $（数字）は無視（bashではコマンドライン引数を入れている）
				end += 2;
				tmp = ft_strdup("");
			}
			else if (word[i] == '$' && (!ft_isalpha(word[i + 1])
					&& word[i + 1] != '_'))
			{
				tmp = ft_strdup("$");//$の1文字を表示
				end += 1;
			}
			else
			{
				// 環境変数展開
				end += 2;//1文字目は確実に英字か_なので2文字目から判定を始める
				while (ft_isalnum(word[end]) || word[end] == '_')
					end++;
				tmp = _ft_help4(word, i, end, env_info);
			}
		}
		else
			tmp = _ft_help3(word, i, &end);
		i = end;
		result = ft_join_free(result, tmp);
	}
	free(word);
	return (result);
}
