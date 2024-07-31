/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:55:05 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/31 11:26:51 by kitaoryoma       ###   ########.fr       */
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
	SIGINT_ERROR = 130,
	SIGQUIT_ERROR = 131,
};

typedef enum e_token_status
{
	NORMAL,
	SINGLE_QUOTE,//'が足りない
	DOUBLE_QUOTE,//"が足りない
	// REDIRECT,// >>>や<<<,<>など不適なリダイレクト
}	t_token_status;

typedef struct s_cmd_info
{
	char	**cmd_argv;
	int		fd_in;
	int		fd_out;
}	t_cmd_info;	


char		**ft_gen_cmds(char *cmd);
// void	ft_exec_cmd(char *cmd, t_env_info env_info);
t_cmd_info	*ft_cmd_info_list(char **cmds, t_env_info *env_info_p);
int			ft_exec_cmdline(t_env_info *env_info_p);
int			ft_exec_cmd(t_cmd_info cmd_info,t_env_info env_info, int read_pipe, int write_pipe);
int			ft_exec_cmd_list(t_cmd_info *cmd_list, t_env_info env_info, int last_index);
char		**ft_gen_tokens(char *input);
char		**ft_gen_cmd_argv(char **tokens, t_env_info env_info);
char		*ft_expand_env(char *word, t_env_info env_info, int is_doublequote);
char		*ft_tokenize(char *str, t_env_info env_info);
int			ft_is_last_redirect(char **tokens);
int			ft_is_redirect(char *str);
int			ft_redirect_err(char **tokens);
int			ft_in_fd(char **tokens, t_env_info env_info, int i);
int			ft_out_fd(char **tokens, t_env_info env_info, int i);
void		ft_in_out_fd(char **tokens, t_env_info env_info, t_cmd_info *cmd_info, int heredoc_fd);
int			ft_heredoc(char **tokens, t_env_info *env_info_p);
int			ft_status_code(int flag, int new_status);
void		ft_sigint_cmd(int sig);
void		ft_sigquit_cmd(int sig);
void		ft_change_g_signum(int sig);

#endif