/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:13:31 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/21 23:18:54 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	ft_is_redirect(char *str)
{
	if (ft_strncmp(str, ">", 2) == 0 || ft_strncmp(str, "<", 2) == 0 || ft_strncmp(str, ">>", 3) == 0 || ft_strncmp(str, "<<", 3) == 0)
		return (1);
	else
		return (0);
}

// リダイレクト先がない、<<< >>>などがないかどうか確認する　あったら1を返す（最後のリダイレクト記号のリダイレクト先がない問題はここではチェックしない）
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
			if (tokens[i + 1] != NULL && ft_is_redirect(tokens[i + 1]))
			{
				ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `%s'\n", tokens[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_is_last_redirect(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	i--;
	if (ft_is_redirect(tokens[i]))
		return (1);
	else
		return (0);
}

// tokens[i]が">>"か">"かを判定して、その後のファイル名を開いて、そのfdを返す
// 出力、追記リダイレクト処理　文法エラー処理はここではしない。エラーがあった場合は-2を返す
int	ft_out_fd(char **tokens, t_env_info env_info, int i)
{
	int		result;
	char	*file;

	file = ft_tokenize(tokens[i + 1], env_info);
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
	else
	{
		result = -1;
		printf("error in ft_out_fd\n");
	}
	if (result == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", file, strerror(errno));
		return (-2);
	}
	return (result);
}
