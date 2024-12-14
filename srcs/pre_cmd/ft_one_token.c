/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:09:42 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 18:21:46 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

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
		*(param.now_p) = _ft_help_one_token(token, env_info, param.utils,
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
