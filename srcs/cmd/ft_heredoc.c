/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:35:53 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/20 21:18:12 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// limiterを求める関数、"や'で囲まれているものはそのまま返す、syntax errorがあればNULLを返す is_quoteはheredoc中に打ち込まれるものを展開する際の場合分けのflagになる
static char	*ft_limit_tokenize(char *str, int *is_quote)
{
	char	*result;
	char	*tmp;
	char	*before;
	int		i;
	int		end;

	result = ft_strdup("");
	i = 0;
	*is_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			end = i + 1;
			while (str[end] != '\0' && str[end] != str[i])
				end++;
			if (str[end] == '\0')
			{
				free(result);
				return (NULL);
			}
			tmp = ft_substr(str, i + 1, end - i - 1);
			end++;
		}
		else
		{
			end = i;
			while (str[end] != '\0' && str[end] != '\"' && str[end] != '\'')
				end++;
			tmp = ft_substr(str, i, end - i);
		}
		before = result;
		result = ft_strjoin(before, tmp);
		free(before);
		free(tmp);
		i = end;
	}
	if (ft_strchr(str, '\'') != NULL || ft_strchr(str, '\"') != NULL)
		*is_quote = 1;
	tmp = result;
	result = ft_strjoin(tmp, "\n");
	free(tmp);
	return (result);
}

// heredocでの入力が入ったfdを返す 一回もheredocがなければ-1 エラーがあれば-2を返す
int	ft_heredoc(char **tokens, t_env_pair *env_list)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		i;
	char	*limiter;
	int		is_quote;
	char	*line;
	char	*tmp;
	int		status;
	int		result;

	i = 0;
	result = -1;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "<<", 3) == 0)
		{
			if (result != -1)
				close(result);
			pipe(pipe_fd);
			pid = fork();
			if (pid == 0)
			{
				close(pipe_fd[0]);
				limiter = ft_limit_tokenize(tokens[i + 1], &is_quote);
				if (limiter == NULL)
				{
					ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
					exit(EXIT_FAILURE);
				}
				while (1)
				{
					line = readline("heredoc > ");
					tmp = line;
					line = ft_strjoin(tmp, "\n");
					free(tmp);
					if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
					{
						free(line);
						break ;
					}
					if (!is_quote)
						line = ft_expand_env(line, env_list, 1);
					write(pipe_fd[1], line, ft_strlen(line));
					free(line);
				}
				close(pipe_fd[1]);
				free(limiter);
				exit(EXIT_SUCCESS);
			}
			close(pipe_fd[1]);
			result = pipe_fd[0];
			wait(&status);
			if (WEXITSTATUS(status) == EXIT_FAILURE)
			{
				close(pipe_fd[0]);
				return (-2);
			}
		}
		i++;
	}
	return (result);
}
