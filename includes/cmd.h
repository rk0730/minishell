/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:55:05 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/02 20:30:50 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "builtins.h"

char		**ft_gen_cmds(char *cmd);
t_cmd_info	*ft_cmd_info_list(char **cmds, t_env_info *env_info_p);
int			ft_exec_cmdline(t_env_info *env_info_p);
int			ft_exec_cmd(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);
int			ft_exec_cmd_list(t_cmd_info *cmd_list, t_env_info env_info, int last_index);
char		**ft_gen_tokens(char *input);
char		**ft_gen_cmd_argv(char **tokens, t_env_info env_info);
char		*ft_expand_env(char *word, t_env_info env_info, int is_doublequote);
char		*ft_tokenize(char *str, t_env_info env_info);
int			ft_is_last_redirect(char **tokens);
int			ft_is_redirect(char *str);
int			ft_redirect_err(char **tokens);
void		ft_in_out_fd(char **tokens, t_env_info env_info, t_cmd_info *cmd_info, int heredoc_fd);
int			ft_heredoc(char **tokens, t_env_info *env_info_p);
void		ft_sigint_cmd(int sig);
void		ft_sigquit_cmd(int sig);
void		ft_change_g_signum(int sig);

#endif