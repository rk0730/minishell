/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_cmd_private.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:57:26 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/11/21 16:45:51 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRE_CMD_PRIVATE_H
# define PRE_CMD_PRIVATE_H

# include "pre_cmd.h"

typedef enum e_token_status
{
	NORMAL,
	SINGLE_QUOTE,//'が足りない
	DOUBLE_QUOTE,//"が足りない
	// REDIRECT,// >>>や<<<,<>など不適なリダイレクト
}	t_token_status;

// モジュール内部でしか使わない関数の宣言を行う　最初に_をつける

char	*_ft_expand_env(char *word, t_env_info env_info, int is_doublequote);
int		_ft_is_redirect(char *str);
int		_ft_skip_quotation(char *input, int i, int *token_status, char c);
char	**_ft_gen_tokens(char *input);
char	**_ft_split_after_index(char *str, int split_index);
char	**_ft_gen_cmd_argv(char **tokens, t_env_info env_info);
char	*_ft_tokenize(char *str, t_env_info env_info);
char	*_ft_expand_normal(char *str, int i, int *endp, t_env_info env_info);
int		_ft_is_last_redirect(char **tokens);
int		_ft_redirect_err(char **tokens);
int		_ft_is_ambiguous_redirect(char *file_name, t_env_info env_info);
void	_ft_in_out_fd(char **tokens, t_env_info env_info, t_cmd_info *cmd_info, int heredoc_fd);
int		_ft_heredoc(char **tokens, t_env_info *env_info_p);

#endif
