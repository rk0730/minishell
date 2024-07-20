/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:18:46 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/20 22:40:55 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// 入力リダイレクト処理　文法エラー処理はここではしない。１つもリダイレクトがない場合は-1を、エラーがあった場合は-2を返す
int	ft_in_file(char **tokens, t_env_pair *env_list)
{
	int		result;
	char	*file;
	int		i;

	i = 0;
	result = -1;
	while (tokens[i] != NULL)
	{
		if (ft_strncmp(tokens[i], "<", 2) == 0)
		{
			if (result != -1)
				close(result);
			file = ft_tokenize(tokens[i + 1], env_list);
			if (file == NULL)
			{
				ft_printf_fd(STDERR_FILENO, "%s: ambiguous redirect\n", tokens[i + 1]);
				return (-2);
			}
			result = open(file, O_RDONLY);
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

// heredocから入力をとるのかfileから入力を取るのか選択する関数
int	ft_in_fd(char **tokens, t_env_pair *env_list)
{
	int	infile_fd;
	int	heredoc_fd;
	int	result;
	int	i;

	heredoc_fd = ft_heredoc(tokens, env_list);
	infile_fd = ft_in_file(tokens, env_list);
	i = 0;
	result = -1;
	while (tokens[i]!= NULL)
	{
		if (ft_strncmp(tokens[i], "<", 2) == 0)
			result = infile_fd;
		else if (ft_strncmp(tokens[i], "<<", 3) == 0)
			result = heredoc_fd;
		i++;
	}
	return (result);
}