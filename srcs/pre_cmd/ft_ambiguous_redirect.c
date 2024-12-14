/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiguous_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:54:42 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/13 15:51:34 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

// ノーマルモードで展開された環境変数に空白文字があったらambiguous redirectと判定する
// リダイレクト記号の次にあるトークンを引数に取り、ambiguous redirectかどうかを判定する
int	_ft_is_ambiguous_redirect(char *file_name, t_env_info env_info)
{
	int		i;
	int		end;
	char	*tmp;
	char	*expanded;

	i = 0;
	while (file_name[i])
	{
		if (file_name[i] == '\"' || file_name[i] == '\'')
		{
			end = i + 1;
			while (file_name[end] != '\0' && file_name[end] != file_name[i])
				end++;
			if (file_name[end] == '\0')
				ft_printf_fd(STDOUT_FILENO,
					"bug in _ft_is_ambiguous_redirect\n");
			i = end + 1;
		}
		else
		{
			expanded = _ft_expand_normal(file_name, i, &end, env_info);
			RKITAO("expanded: %s\n", expanded);
			tmp = expanded;
			while (*tmp)
			{
				if (ft_isspace(*tmp) == 1)
				{
					free(expanded);
					return (1);
				}
				tmp++;
			}
			free(expanded);
			i = end;
		}
	}
	return (0);
}
