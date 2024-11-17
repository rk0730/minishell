/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:12:46 by rkitao            #+#    #+#             */
/*   Updated: 2024/11/17 18:29:39 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

// ""や''を開き、""なら中身をexpand_env、''ならそのまま返す
static char	*ft_help1(char *str, int i, int *endp, t_env_info env_info)
{
	char	*tmp;
	char	*result;

	if (str[i] == '\"')
	{
		*endp = i + 1;
		while (str[*endp] != '\0' && str[*endp] != '\"')
			(*endp)++;
		(*endp)++;
		tmp = ft_substr(str, i + 1, *endp - i - 2);
		result = _ft_expand_env(tmp, env_info, 1);
		return (result);
	}
	else if (str[i] == '\'')
	{
		*endp = i + 1;
		while (str[*endp] != '\0' && str[*endp] != '\'')
			(*endp)++;
		(*endp)++;
		return (ft_substr(str, i + 1, *endp - i - 2));
	}
	ft_printf_fd(STDERR_FILENO, "error in ft_tokenize ft_help1\n");
	return (NULL);
}

// $"や$'の時は飛ばす　それ以外の$はexpand_envする
// ""や''で囲まれていない文字列をexpand_envする
static char	*ft_help2(char *str, int i, int *endp, t_env_info env_info)
{
	char	*tmp;
	char	*result;

	*endp = i;
	while (str[*endp] != '\0' && str[*endp] != '\"' && str[*endp] != '\'')
		(*endp)++;
	// 末尾が$"や$'の時は$を無視する
	if (str[*endp - 1] == '$' && (str[*endp] == '\'' || str[*endp] == '\"'))
		tmp = ft_substr(str, i, *endp - i - 1);
	else
		tmp = ft_substr(str, i, *endp - i);
	result = _ft_expand_env(tmp, env_info, 0);
	return (result);
}

// static char	*ft_help4(int *ip, int end, char **old_p, char **tmp_p)
// {
// 	char	*result;

// 	*ip = end;
// 	result = ft_strjoin(*old_p, *tmp_p);
// 	free(*old_p);
// 	free(*tmp_p);
// 	return (result);
// }

// ""で囲まれているものはft_expand_envで環境変数展開、''で囲まれていたらそのままつなげる
char	*_ft_tokenize(char *str, t_env_info env_info)
{
	char	*result;
	char	*tmp;
	// char	*before;
	int		i;
	int		end;

	result = ft_strdup("");
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			tmp = ft_help1(str, i, &end, env_info);
		else
			tmp = ft_help2(str, i, &end, env_info);
		i = end;
		result = ft_join_free(result, tmp);
	}
	if (ft_strchr(str, '\'') == NULL && ft_strchr(str, '\"') == NULL && ft_strlen(result) == 0)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

// tokenの各文字列が"で挟まれていたら環境変数展開したり、'で挟まれていたらそれを除く（リダイレクトは飛ばす）
char	**_ft_gen_cmd_argv(char **tokens, t_env_info env_info)
{
	char	**cmd_argv;
	char	*tmp;
	int		i;
	// int		last_index;

	i = 0;
	cmd_argv = (char **)malloc(sizeof(char *));
	// last_index = 0;
	if (!cmd_argv)
		return (NULL);
	cmd_argv[0] = NULL;
	while (tokens[i])
	{
		//リダイレクト関連の文字列だったら飛ばす
		// if (ft_strncmp(tokens[i], ">", 2) == 0 || ft_strncmp(tokens[i], "<", 2) == 0 || ft_strncmp(tokens[i], "<<", 3) == 0 || ft_strncmp(tokens[i], ">>", 3) == 0)
		if (_ft_is_redirect(tokens[i]))
		{
			i += 2;
			continue ;
		}
		// if (!tokens[i + 1])
		// 	last_index = 1;
		// printf("last index flag: %d\n", last_index);
		tmp = _ft_tokenize(tokens[i], env_info);
		if (tmp != NULL)
			cmd_argv = ft_add_str(cmd_argv, tmp);
		i++;
	}
	return (cmd_argv);
}
