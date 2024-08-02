/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:12:46 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/02 16:54:52 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static char	*ft_help1(char *str, int i, int *endp, t_env_info env_info)
{
	if (str[i] == '\"')
	{
		*endp = i + 1;
		while (str[*endp] != '\0' && str[*endp] != '\"')
			(*endp)++;
		(*endp)++;
		return (ft_expand_env(ft_substr(str, i + 1, *endp - i - 2), env_info, 1));
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

static char	*ft_help2(char *str, int i, int *endp, t_env_info env_info)
{
	if (str[i] == '$' && str[i + 1] == '\0')//$の1文字だけの場合のみ例外処理、$と表示するため
	{
		*endp = i + 1;
		return (ft_strdup("$"));
	}
	else
	{
		*endp = i;
		while (str[*endp] != '\0' && str[*endp] != '\"' && str[*endp] != '\'')
			(*endp)++;
		return (ft_expand_env(ft_substr(str, i, *endp - i), env_info, 0));
	}
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

// ""で囲まれているものはft_expand_envで環境変数展開、''で囲まれていたらそのままつなげる
char	*ft_tokenize(char *str, t_env_info env_info)
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
		result = ft_help4(&i, end, &result, &tmp);
	}
	if (ft_strchr(str, '\'') == NULL && ft_strchr(str, '\"') == NULL && ft_strlen(result) == 0)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

// tokenの各文字列が"で挟まれていたら環境変数展開したり、'で挟まれていたらそれを除く（リダイレクトは飛ばす）
char	**ft_gen_cmd_argv(char **tokens, t_env_info env_info)
{
	char	**cmd_argv;
	char	*tmp;
	int		i;

	i = 0;
	cmd_argv = (char **)malloc(sizeof(char *));
	if (!cmd_argv)
		return (NULL);
	cmd_argv[0] = NULL;
	while (tokens[i])
	{
		//リダイレクト関連の文字列だったら飛ばす
		// if (ft_strncmp(tokens[i], ">", 2) == 0 || ft_strncmp(tokens[i], "<", 2) == 0 || ft_strncmp(tokens[i], "<<", 3) == 0 || ft_strncmp(tokens[i], ">>", 3) == 0)
		if (ft_is_redirect(tokens[i]))
		{
			i += 2;
			continue ;
		}
		tmp = ft_tokenize(tokens[i], env_info);
		if (tmp != NULL)
			cmd_argv = ft_add_str(cmd_argv, tmp);
		i++;
	}
	return (cmd_argv);
}
