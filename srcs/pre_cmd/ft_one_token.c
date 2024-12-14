/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:09:42 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 17:34:30 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

typedef struct s_param
{
	int		*utils;
	char	**now_p;
	char	***tmp_array_p;
	t_bool	*last_add_p;
	char	***cmd_argv_p;
}			t_param;

// array1のlen1個とarray2のlen2個をつなげる
static char	**_ft_join_array(char **array1, char **array2, int len1, int len2)
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

static char	*_ft_help1(char *token, t_env_info env_info, int *utils, char *now)
{
	char	*tmp;

	utils[2] = utils[1];
	while (token[utils[2]] && token[utils[2]] != '\''
		&& token[utils[2]] != '\"')
		utils[2]++;
	if (token[utils[2] - 1] == '$' && (token[utils[2]] == '\''
			|| token[utils[2]] == '\"'))
		tmp = ft_substr(token, utils[1], utils[2] - utils[1] - 1);
	else
		tmp = ft_substr(token, utils[1], utils[2] - utils[1]);
	now = ft_join_free(now, _ft_tokenize(tmp, env_info));
	free(tmp);
	return (now);
}

static void	_ft_help2(char **now_p, t_bool *last_add_p, char **tmp_array,
		char ***cmd_argv_p)
{
	if (tmp_array[0] != NULL)
	{
		*last_add_p = TRUE;
		*now_p = tmp_array[ft_array_len(tmp_array) - 1];
		*cmd_argv_p = _ft_join_array(*cmd_argv_p, tmp_array,
				ft_array_len(*cmd_argv_p), ft_array_len(tmp_array) - 1);
	}
	else
	{
		*last_add_p = FALSE;
		*now_p = ft_strdup("");
		free(tmp_array);
	}
}

static void	_ft_help3(char *token, t_env_info env_info, char **now_p,
		int *utils)
{
	char	*tmp;

	utils[2] = utils[1] + 1;
	while (token[utils[2]] != token[utils[1]])
		utils[2]++;
	tmp = ft_substr(token, utils[1], utils[2] - utils[1] + 1);
	*now_p = ft_join_free(*now_p, _ft_tokenize(tmp, env_info));
	free(tmp);
	utils[0] = ft_strlen(*now_p);
	utils[1] = utils[2] + 1;
}

static void	_ft_help4(t_bool *last_add_p, char ***cmd_argv_p, char **tmp_array,
		char **now_p)
{
	*last_add_p = FALSE;
	*cmd_argv_p = _ft_join_array(*cmd_argv_p, tmp_array,
			ft_array_len(*cmd_argv_p), ft_array_len(tmp_array));
	*now_p = ft_strdup("");
}

static void	_ft_help5(t_param param, char *token, t_env_info env_info)
{
	char	*tmp;

	if (token[param.utils[1]] != '\'' && token[param.utils[1]] != '\"')
	{
		*(param.now_p) = _ft_help1(token, env_info, param.utils,
				*(param.now_p));
		*(param.tmp_array_p) = _ft_split_after_index(*(param.now_p),
				param.utils[0]);
		tmp = *(param.now_p);
		if (ft_strlen(tmp) > 0 && ft_isspace(tmp[ft_strlen(tmp) - 1]))
			_ft_help4(param.last_add_p, param.cmd_argv_p, *(param.tmp_array_p),
				param.now_p);
		else
			_ft_help2(param.now_p, param.last_add_p, *(param.tmp_array_p),
				param.cmd_argv_p);
		free(tmp);
		param.utils[0] = 0;
		param.utils[1] = param.utils[2];
	}
	else
	{
		*(param.last_add_p) = TRUE;
		_ft_help3(token, env_info, param.now_p, param.utils);
	}
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
	t_bool	last_add;
	t_param	param;

	param.cmd_argv_p = &cmd_argv;
	now = ft_strdup("");
	param.now_p = &now;
	param.utils = (int *)malloc(sizeof(int) * 3);
	param.utils[1] = 0;
	param.utils[0] = 0;
	last_add = TRUE;
	param.last_add_p = &last_add;
	param.tmp_array_p = (char ***)malloc(sizeof(char **));
	while (token[param.utils[1]])
		_ft_help5(param, token, env_info);
	if (*(param.last_add_p))
		cmd_argv = ft_add_str(cmd_argv, *(param.now_p));
	else
		free(*(param.now_p));
	free(param.utils);
	free(param.tmp_array_p);
	return (*(param.cmd_argv_p));
}
