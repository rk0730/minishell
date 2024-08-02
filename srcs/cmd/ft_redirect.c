/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:13:31 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/02 15:24:25 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// リダイレクト記号かどうかを判定する
int	ft_is_redirect(char *str)
{
	if (ft_strncmp(str, ">", 2) == 0 || ft_strncmp(str, "<", 2) == 0 || ft_strncmp(str, ">>", 3) == 0 || ft_strncmp(str, "<<", 3) == 0)
		return (1);
	else
		return (0);
}

// リダイレクト先がない、<<< >>>などがないかどうか確認する　あったら1を返す（最後のリダイレクト記号のリダイレクト先がない問題はここではチェックしない）
int	ft_redirect_err(char **tokens)
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

// 最後がリダイレクト記号でないかどうかチェックする
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
