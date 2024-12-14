/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_syntaxerr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:59:27 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 18:04:29 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static int	_ft_heredoc_syntaxerr_h(char **tokens)
{
	int	j;

	j = 0;
	while (j < ft_array_len(tokens) - 1)
	{
		if (ft_strncmp(tokens[j], "<<", 3) == 0 && _ft_is_redirect(
				tokens[j + 1]))
		{
			ft_printf_fd(STDERR_FILENO, "syntax error\n");
			ft_free_array(tokens);
			return (1);
		}
		j++;
	}
	return (0);
}

int	_ft_heredoc_syntax_err(char **cmds)
{
	int		i;
	char	**tokens;

	i = 0;
	while (i < ft_array_len(cmds))
	{
		tokens = _ft_gen_tokens(cmds[i]);
		if (_ft_heredoc_syntaxerr_h(tokens))
			return (1);
		if (ft_strncmp(tokens[ft_array_len(tokens) - 1], "<<", 3) == 0)
		{
			ft_printf_fd(STDERR_FILENO, "syntax error\n");
			ft_free_array(tokens);
			return (1);
		}
		ft_free_array(tokens);
		i++;
	}
	return (0);
}
