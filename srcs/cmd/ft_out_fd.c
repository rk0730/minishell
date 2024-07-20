/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:13:31 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/20 22:41:19 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	ft_is_redirect(char *str)
{
	if (ft_strncmp(str, ">", 2) == 0 || ft_strncmp(str, "<", 2) == 0 || ft_strncmp(str, ">>", 3) == 0 || ft_strncmp(str, "<<", 3) == 0)
		return (1);
	else
		return (0);
}

// リダイレクト先がない、<<< >>>などがないかどうか確認する　あったら1を返す
int	ft_fd_error(char **tokens)
{
	int	i;


	i = 0;
	while (tokens[i])
	{
		// >>>や<<<などの処理 bashの挙動とやや異なるが、ここはディフェンスできる気がする　一旦シンプルに作る
		if ((tokens[i][0] == '>' || tokens[i][0] == '<') && ft_is_redirect(tokens[i]) == 0)
		{
			ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `%s'\n", tokens[i]);
			return (1);
		}
		// リダイレクト先がない場合の処理
		if (ft_is_redirect(tokens[i]))
		{
			if (tokens[i + 1] == NULL || ft_is_redirect(tokens[i + 1]))
			{
				ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `%s'\n", tokens[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

// 出力、追記リダイレクト処理　文法エラー処理はここではしない。１つもリダイレクトがない場合は-1を、エラーがあった場合は-2を返す
int	ft_out_fd(char **tokens, t_env_pair *env_list)
{
	int		result;
	char	*file;
	int		i;

	i = 0;
	result = -1;
	while (tokens[i] != NULL)
	{
		if (ft_strncmp(tokens[i], ">", 1) == 0)
		{
			if (result != -1)
				close(result);
			file = ft_tokenize(tokens[i + 1], env_list);
			if (file == NULL)
			{
				ft_printf_fd(STDERR_FILENO, "%s: ambiguous redirect\n", tokens[i + 1]);
				return (-2);
			}
			if (ft_strncmp(tokens[i], ">", 2) == 0)
			{
				result = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			else if (ft_strncmp(tokens[i], ">>", 3) == 0)
				result = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (result == -1)
			{
				ft_printf_fd(STDERR_FILENO, "%s: %s\n", file, strerror(errno));
				return (-2);
			}
		}
		i++;
	}
	return (result);
}
