/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:35:53 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/28 16:11:27 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// クォーテーションエラーがあった際はNULLを返すように作ったが、最初にクォーテーションはチェックしているため、ここでそのエラーが出ることはなさそう
// limiterを求める関数、"や'で囲まれているものはそのまま返す、 is_quoteはheredoc中に打ち込まれるものを展開する際の場合分けのflagになる
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

// heredocでの入力が入ったfdを返す 一回もheredocがなければ-1 エラーがあれば-2を返す fork使わないものに書き直し
int	ft_heredoc(char **tokens, t_env_info *env_info_p)
{
	int		pipe_fd[2];
	// pid_t	pid;
	int		i;
	char	*limiter;
	int		is_quote;
	char	*line;
	char	*tmp;
	// int		status;
	int		result;

	i = 0;
	result = -1;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "<<", 3) == 0)
		{
			if (result == -1)
			{
				tmp = env_info_p->input;
				env_info_p->input = ft_strjoin(tmp, "\n");
				free(tmp);
			}
			else
			{
				close(result);
			}
			if (tokens[i + 1] == NULL)//最後に<<がある場合、あとでエラー文は出すのでここでは出さない
				return (-2);
			pipe(pipe_fd);
			// close(pipe_fd[0]);
			limiter = ft_limit_tokenize(tokens[i + 1], &is_quote);
			if (limiter == NULL)
			{
				ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
				return (-2);
			}
			while (1)
			{
				line = readline("heredoc > ");
				tmp = line;
				line = ft_strjoin(tmp, "\n");
				free(tmp);
				tmp = env_info_p->input;
				env_info_p->input = ft_strjoin(tmp, line);
				free(tmp);
				if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
				{
					free(line);
					break ;
				}
				if (!is_quote)
					line = ft_expand_env(line, *env_info_p, 1);
				write(pipe_fd[1], line, ft_strlen(line));
				free(line);
			}
			close(pipe_fd[1]);
			free(limiter);
			result = pipe_fd[0];
		}
		i++;
	}
	return (result);
}

// heredocでの入力が入ったfdを返す 一回もheredocがなければ-1 エラーがあれば-2を返す
// int	ft_heredoc(char **tokens, t_env_info *env_info_p)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid;
// 	int		i;
// 	char	*limiter;
// 	int		is_quote;
// 	char	*line;
// 	char	*tmp;
// 	int		status;
// 	int		result;

// 	i = 0;
// 	result = -1;
// 	while (tokens[i])
// 	{
// 		if (ft_strncmp(tokens[i], "<<", 3) == 0)
// 		{
// 			if (result != -1)
// 				close(result);
// 			if (tokens[i + 1] == NULL)//最後に<<がある場合、あとでエラー文は出すのでここでは出さない
// 				return (-2);
// 			pipe(pipe_fd);
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				close(pipe_fd[0]);
// 				limiter = ft_limit_tokenize(tokens[i + 1], &is_quote);
// 				if (limiter == NULL)
// 				{
// 					ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
// 					exit(EXIT_FAILURE);
// 				}
// 				tmp = env_info_p->input;
// 				env_info_p->input = ft_strjoin(tmp, "\n");
// 				free(tmp);
// 				while (1)
// 				{
// 					line = readline("heredoc > ");
// 					tmp = line;
// 					line = ft_strjoin(tmp, "\n");
// 					free(tmp);
// 					tmp = env_info_p->input;
// 					env_info_p->input = ft_strjoin(tmp, line);
// 					free(tmp);
// 					if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
// 					{
// 						printf("heredoc end : %s\n", env_info_p->input);
// 						free(line);
// 						break ;
// 					}
// 					if (!is_quote)
// 						line = ft_expand_env(line, *env_info_p, 1);
// 					write(pipe_fd[1], line, ft_strlen(line));
// 					free(line);
// 				}
// 				close(pipe_fd[1]);
// 				free(limiter);
// 				exit(EXIT_SUCCESS);
// 			}
// 			else
// 			{
// 				close(pipe_fd[1]);
// 				result = pipe_fd[0];
// 				wait(&status);
// 				printf("parent : %s\n", env_info_p->input);
// 				if (WEXITSTATUS(status) == EXIT_FAILURE)
// 				{
// 					close(pipe_fd[0]);
// 					return (-2);
// 				}
// 			}
// 			printf("after fork : %s\n", env_info_p->input);
// 		}
// 		i++;
// 	}
// 	printf("input : %s\n", env_info_p->input);
// 	return (result);
// }
