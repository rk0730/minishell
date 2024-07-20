/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:44:39 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/07/20 20:56:36 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// strの環境変数を展開した文字列を返す doubleqouteが1なら"で囲まれているものを展開,0なら"で囲まれているわけではない　$の処理でこのフラグが必要
char	*ft_expand_env(char *word, t_env_pair *env_list, int is_doublequote)
{
	char	*result;
	char	*tmp;
	char	*before;
	int		i;
	int		end;

	result = ft_strdup("");
	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			// if (word[i+1] == '\"' || word[i+1] == '\'')
			// {
			// 	i++;
			// 	continue ;
			// }
			end = i;
			while (word[end] != '\0' && word[end] != ' ' && word[end] != '\"' && word[end] != '\'' && word[end]!= '\n')
				end++;
			if (end - i == 1)
			{
				if (is_doublequote == 1)
					tmp = ft_strdup("$");
				else
					tmp = ft_strdup("");//""で囲まれているわけではなく、$の後ろに何もない場合は何も返さない
			}
			else
				tmp = ft_search_env(ft_substr(word, i + 1, end - i - 1), env_list);
		}
		else
		{
			end = i;
			while (word[end] != '\0' && word[end] != '$')
				end++;
			tmp = ft_substr(word, i, end - i);
		}
		before = result;
		result = ft_strjoin(before, tmp);
		free(before);
		free(tmp);
		i = end;
	}
	return (result);
}

// ""で囲まれているものはft_expand_envで環境変数展開、''で囲まれていたらそのままつなげる
char	*ft_tokenize(char *str, t_env_pair *env_list)
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
		if (str[i] == '\"')
		{
			end = i + 1;
			while (str[end] != '\0' && str[end] != '\"')
				end++;
			tmp = ft_expand_env(ft_substr(str, i + 1, end - i - 1), env_list, 1);
			end++;
		}
		else if (str[i] == '\'')
		{
			end = i + 1;
			while (str[end] != '\0' && str[end] != '\'')
				end++;
			tmp = ft_substr(str, i + 1, end - i - 1);
			end++;
		}
		else
		{
			if (str[i] == '$' && str[i + 1] == '\0')//$の1文字だけの場合のみ例外処理、$と表示するため
			{
				tmp = ft_strdup("$");
				end = i + 1;
			}
			else
			{
				end = i;
				while (str[end] != '\0' && str[end] != '\"' && str[end] != '\'')
					end++;
				tmp = ft_expand_env(ft_substr(str, i, end - i), env_list, 0);
			}
		}
		before = result;
		result = ft_strjoin(before, tmp);
		free(before);
		free(tmp);
		i = end;
	}
	if (ft_strchr(str, '\'') == NULL && ft_strchr(str, '\"') == NULL && ft_strlen(result) == 0)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

// tokenの各文字列が"で挟まれていたら環境変数展開したり、'で挟まれていたらそれを除く（リダイレクトは飛ばす）
char	**ft_gen_cmd_array(char **tokens, t_env_pair *env_list)
{
	char	**cmd_array;
	char	*tmp;
	int		i;

	i = 0;
	cmd_array = (char **)malloc(sizeof(char *));
	if (!cmd_array)
		return (NULL);
	cmd_array[0] = NULL;
	while (tokens[i])
	{
		//リダイレクト関連の文字列だったら飛ばす
		if (ft_strncmp(tokens[i], ">", 2) == 0 || ft_strncmp(tokens[i], "<", 2) == 0 || ft_strncmp(tokens[i], "<<", 3) == 0 || ft_strncmp(tokens[i], ">>", 3) == 0)
		{
			i += 2;
			continue ;
		}
		tmp = ft_tokenize(tokens[i], env_list);
		if (tmp != NULL)
			cmd_array = ft_add_str(cmd_array, tmp);
		i++;
	}
	return (cmd_array);
}
