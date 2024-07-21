/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:18:46 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/21 23:19:24 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// 入力リダイレクト処理　文法エラー処理はここではしない。エラーがあった場合は-2を返す
int	ft_in_fd(char **tokens, t_env_info env_info, int i)
{
	int		result;
	char	*file;

	file = ft_tokenize(tokens[i + 1], env_info);
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
	return (result);
}

// // heredocから入力をとるのかfileから入力を取るのか選択する関数
// int	ft_in_fd(char **tokens, t_env_pair *env_list)
// {
// 	int	infile_fd;
// 	int	heredoc_fd;
// 	int	result;
// 	int	i;

// 	heredoc_fd = ft_heredoc(tokens, env_list);
// 	infile_fd = ft_in_file(tokens, env_list);
// 	i = 0;
// 	result = -1;
// 	while (tokens[i]!= NULL)
// 	{
// 		if (ft_strncmp(tokens[i], "<", 2) == 0)
// 			result = infile_fd;
// 		else if (ft_strncmp(tokens[i], "<<", 3) == 0)
// 			result = heredoc_fd;
// 		i++;
// 	}
// 	return (result);
// }