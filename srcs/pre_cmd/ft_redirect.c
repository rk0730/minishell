/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:13:31 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/13 15:26:15 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

// リダイレクト記号かどうかを判定する
int	_ft_is_redirect(char *str)
{
	if (ft_strncmp(str, ">", 2) == 0 || ft_strncmp(str, "<", 2) == 0
		|| ft_strncmp(str, ">>", 3) == 0 || ft_strncmp(str, "<<", 3) == 0)
		return (1);
	else
		return (0);
}

// リダイレクト先がない、<<< >>>などがないかどうか確認する　あったら1を返す
// （最後のリダイレクト記号のリダイレクト先がない問題はここではチェックしない）
int	_ft_redirect_err(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		// >>>や<<<などの処理 bashの挙動とやや異なるが、ここはディフェンスできる気がする　一旦シンプルに作る
		if ((tokens[i][0] == '>' || tokens[i][0] == '<')
			&& _ft_is_redirect(tokens[i]) == 0)
		{
			ft_printf_fd(STDERR_FILENO,
				"syntax error near unexpected token `%s'\n", tokens[i]);
			return (1);
		}
		// リダイレクト先がない場合の処理
		if (_ft_is_redirect(tokens[i]))
		{
			if (tokens[i + 1] != NULL && _ft_is_redirect(tokens[i + 1]))
			{
				ft_printf_fd(STDERR_FILENO,
					"syntax error near unexpected token `%s'\n", tokens[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

// 最後がリダイレクト記号でないかどうかチェックする
int	_ft_is_last_redirect(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	i--;
	if (_ft_is_redirect(tokens[i]))
		return (1);
	else
		return (0);
}
