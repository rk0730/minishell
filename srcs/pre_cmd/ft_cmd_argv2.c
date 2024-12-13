/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_argv2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:09:42 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/13 15:50:47 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

// array1のlen1個とarray2のlen2個をつなげる
static char	**_ft_join_array(char	**array1, char **array2, int len1, int len2)
{
	char	**new_array;
	int		i;

	new_array = (char **)malloc(sizeof(char *) * (len1 + len2 + 1));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		new_array[i] = array1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		new_array[i] = array2[i - len1];
		i++;
	}
	new_array[i] = NULL;
	free(array1);
	free(array2);
	return (new_array);
}

// トークンと現在のcmd_argvを引数に取り、トークンを展開し、cmd_argvに追加して返す
/*
	
	・char	*now;
	⇨ 次にcmd_argvに追加する文字列
	・char	*tmp;	
	・char	**tmp_array;
	→ cmd_argvに追加する文字列配列
	・int		utils[3]
		0: int		split_index;
		→tokenを分割する際はこのsplit_index以降で分割する　
		→tokenに"や'があるときは空白文字で分割しないで次に進む必要があるため
		1: int		i;
		2: int		end;
	⇨ iとendでtokenのindexを管理する
*/
char	**_ft_one_token(char *token, char **cmd_argv, t_env_info env_info)
{
	char	*now;
	char	*tmp;
	char	**tmp_array;
	int		utils[3];
	t_bool	last_add;

	now = ft_strdup("");
	utils[1] = 0;
	utils[0] = 0;
	last_add = TRUE;
	while (token[utils[1]])
	{
		// クウォーテーションに囲まれてないときの処理　囲まれてない文字列は空白文字で区切る必要があるため場合分けをしている
		if (token[utils[1]] != '\'' && token[utils[1]] != '\"')
		{
			utils[2] = utils[1];
			while (token[utils[2]] && token[utils[2]] != '\''
				&& token[utils[2]] != '\"')
				utils[2]++;
			// 環境変数を展開してnow文字列に追加する
			// $'や$"の時は$を飛ばす
			if (token[utils[2] - 1] == '$'
				&& (token[utils[2]] == '\'' || token[utils[2]] == '\"'))
				tmp = ft_substr(token, utils[1], utils[2] - utils[1] - 1);
			else
				tmp = ft_substr(token, utils[1], utils[2] - utils[1]);
			RKITAO("now : %s\n", now);
			// RKITAO("tokenize : %s\n", _ft_tokenize(tmp, env_info));
			now = ft_join_free(now, _ft_tokenize(tmp, env_info));
			free(tmp);
			// utils[0]以降で空白文字で分割し、cmd_argvに追加する
			RKITAO("now: %s\nutils[0]: %d\n"
				"call _ft_split_after_index\n", now, utils[0]);
			tmp_array = _ft_split_after_index(now, utils[0]);
			tmp = now;
			// nowの末尾が空白文字の場合はそこで区切るが、そうでない場合は次の要素と繋げる
			if (ft_strlen(tmp) > 0 && ft_isspace(tmp[ft_strlen(tmp) - 1]))
			{
				RKITAO("last of now is space\n");
				last_add = FALSE;// 空白文字で終わっているので、最後に追加するnowはない
				cmd_argv = _ft_join_array(cmd_argv, tmp_array,
						ft_array_len(cmd_argv), ft_array_len(tmp_array));
				now = ft_strdup("");
			}
			else
			{
				// 次の要素をnowに繋げるために、nowにはtmp_arrayの最後の要素を入れ、それ以外をcmd_argvに追加する
				if (tmp_array[0] != NULL)
				{
					last_add = TRUE;
					now = tmp_array[ft_array_len(tmp_array) - 1];
					cmd_argv = _ft_join_array(cmd_argv, tmp_array,
							ft_array_len(cmd_argv),
							ft_array_len(tmp_array) - 1);
				}
				else
				{
					last_add = FALSE;
					now = ft_strdup("");
					free(tmp_array);
				}
			}
			RKITAO("now: %s\n", now);
			free(tmp);
			utils[0] = 0;
			utils[1] = utils[2];
		}
		else
		{
			// クウォーテーションに囲まれている際はnowに繋げるだけで分割をする必要はない
			last_add = TRUE;
			utils[2] = utils[1] + 1;
			// クウォーテーションエラーはないことがわかっているので必ず閉じくくりがある
			while (token[utils[2]] != token[utils[1]])
				utils[2]++;
			tmp = ft_substr(token, utils[1], utils[2] - utils[1] + 1);
			RKITAO("tmp: %s\n", tmp);
			now = ft_join_free(now, _ft_tokenize(tmp, env_info));
			free(tmp);
			// クウォーテーションがある際は分割しないのでutils[0]をnowの最後にする
			utils[0] = ft_strlen(now);
			RKITAO("now: %s\n", now);
			RKITAO("utils[0]: %d\n", utils[0]);
			utils[1] = utils[2] + 1;
		}
	}
	// 最後の文字列をcmd_argvに追加する
	if (last_add)
		cmd_argv = ft_add_str(cmd_argv, now);
	else
		free(now);
	return (cmd_argv);
}
