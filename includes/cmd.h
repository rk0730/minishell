/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:55:05 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/20 21:33:58 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "env.h"
# include "utils.h"

enum e_cmd_error
{
	CMD_ERROR = 1,
	CMD_NOT_FOUND = 127,
	SYNTAX_ERROR = 2,
};

typedef enum e_token_status
{
	NORMAL,
	SINGLE_QUOTE,//'が足りない
	DOUBLE_QUOTE,//"が足りない
	REDIRECT,// >>>や<<<,<>など不適なリダイレクト
}	t_token_status;

typedef struct s_cmd_info
{
	char	**cmd_array;
	int		fd_in;
	int		fd_out;
}	t_cmd_info;	


void	ft_exec_cmd(char *cmd, t_env_pair *env_list);
char	**ft_gen_tokens(char *input);
char	**ft_gen_cmd_array(char **tokens, t_env_pair *env_list);
char	*ft_expand_env(char *word, t_env_pair *env_list, int is_doublequote);
char	*ft_tokenize(char *str, t_env_pair *env_list);
int		ft_fd_error(char **tokens);
int		ft_in_fd(char **tokens, t_env_pair *env_list);
int		ft_out_fd(char **tokens, t_env_pair *env_list);
int		ft_heredoc(char **tokens, t_env_pair *env_list);

#endif