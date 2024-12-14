/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_cmd_private.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:57:26 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 18:15:39 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRE_CMD_PRIVATE_H
# define PRE_CMD_PRIVATE_H

# include "pre_cmd.h"

typedef enum e_token_status
{
	NORMAL,
	SINGLE_QUOTE, //'が足りない
	DOUBLE_QUOTE, //"が足りない
					// REDIRECT,// >>>や<<<,<>など不適なリダイレクト
}		t_token_status;

typedef struct s_param
{
	int		*utils;
	char	**now_p;
	char	***tmp_array_p;
	t_bool	*last_add_p;
	char	***cmd_argv_p;
}			t_param;

// モジュール内部でしか使わない関数の宣言を行う　最初に_をつける

char	*_ft_expand_env(char *word, t_env_info env_info, int is_doublequote);
int		_ft_is_redirect(char *str);
int		_ft_skip_quotation(char *input, int i, int *token_status, char c);
char	**_ft_gen_tokens(char *input);
char	**_ft_split_after_index(char *str, int split_index);
char	**_ft_join_array(char **array1, char **array2, int len1, int len2);
char	*_ft_help_one_token(char *token, t_env_info env_info, int *utils, char *now);
char	**_ft_one_token(char *token, char **cmd_argv, t_env_info env_info);
char	**_ft_gen_cmd_argv(char **tokens, t_env_info env_info);
char	*_ft_tokenize(char *str, t_env_info env_info);
char	*_ft_expand_normal(char *str, int i, int *endp, t_env_info env_info);
int		_ft_is_last_redirect(char **tokens);
int		_ft_redirect_err(char **tokens);
int		_ft_is_ambiguous_redirect(char *file_name, t_env_info env_info);
void	_ft_in_out_fd(char **tokens, t_env_info env_info, t_cmd_info *cmd_info,
			int heredoc_fd);
char	*_ft_limit_tokenize(char *str, int *is_quote);
int		_ft_heredoc_write_fd(int flag, int fd);
int		_ft_one_heredoc(t_env_info *env_info_p, int pipe_fd[2], char *limiter,
			int is_quote);
int		_ft_heredoc(char **tokens, t_env_info *env_info_p);
void	_ft_sigint_heredoc(int sig);
void	_ft_close_all_fd(int fd);
void	_ft_change_g_signum(int sig);
int		_ft_in_fd(char **tokens,
		t_cmd_info *cmd_info, t_env_info env_info, int i);
int		_ft_out_fd(char **tokens, t_env_info env_info, int i);
int		_ft_heredoc_syntax_err(char **cmds);

#endif
