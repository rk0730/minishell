/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:39:02 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 18:08:14 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static void	_ft_help1(char **tokens, char **file, int i)
{
	if (ft_strchr(tokens[i + 1], '\'') == NULL
		&& ft_strchr(tokens[i + 1], '\"') == NULL && ft_strlen(*file) == 0)
	{
		free(*file);
		(*file) = NULL;
	}
}

int	_ft_in_fd(char **tokens,
		t_cmd_info *cmd_info, t_env_info env_info, int i)
{
	int		result;
	char	*file;

	file = _ft_tokenize(tokens[i + 1], env_info);
	_ft_help1(tokens, &file, i);
	if (file == NULL || _ft_is_ambiguous_redirect(tokens[i + 1], env_info) == 1)
	{
		free(file);
		ft_printf_fd(STDERR_FILENO, "%s: ambiguous redirect\n", tokens[i + 1]);
		ft_close(cmd_info->fd_in, 35);
		return (-2);
	}
	result = open(file, O_RDONLY);
	if (result == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", file, strerror(errno));
		free(file);
		ft_close(cmd_info->fd_in, 35);
		return (-2);
	}
	free(file);
	return (result);
}

int	_ft_out_fd(char **tokens, t_env_info env_info, int i)
{
	int		result;
	char	*file;

	result = 0;
	file = _ft_tokenize(tokens[i + 1], env_info);
	_ft_help1(tokens, &file, i);
	if (file == NULL || _ft_is_ambiguous_redirect(tokens[i + 1], env_info) == 1)
	{
		free(file);
		ft_printf_fd(STDERR_FILENO, "%s: ambiguous redirect\n", tokens[i + 1]);
		return (-2);
	}
	if (ft_strncmp(tokens[i], ">", 2) == 0)
		result = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strncmp(tokens[i], ">>", 3) == 0)
		result = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (result == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", file, strerror(errno));
		free(file);
		return (-2);
	}
	free(file);
	return (result);
}
