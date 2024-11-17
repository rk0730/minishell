/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_cmd_private.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:57:26 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/11/17 18:49:27 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRE_CMD_PRIVATE_H
# define PRE_CMD_PRIVATE_H

# include "pre_cmd.h"

// モジュール内部でしか使わない関数の宣言を行う　最初に_をつける

char	*_ft_expand_env(char *word, t_env_info env_info, int is_doublequote);
int		_ft_is_redirect(char *str);
char	**_ft_gen_tokens(char *input);
char	**_ft_gen_cmd_argv(char **tokens, t_env_info env_info);
char	*_ft_tokenize(char *str, t_env_info env_info);
int		_ft_is_last_redirect(char **tokens);
int		_ft_redirect_err(char **tokens);
void	_ft_in_out_fd(char **tokens, t_env_info env_info, t_cmd_info *cmd_info, int heredoc_fd);
int		_ft_heredoc(char **tokens, t_env_info *env_info_p);

#endif
