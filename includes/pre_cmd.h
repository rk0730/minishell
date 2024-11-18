/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_cmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:55:40 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/11/18 09:25:02 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRE_CMD_H
# define PRE_CMD_H

# include "env.h"

typedef struct s_cmd_info
{
	char	**cmd_argv;
	int		fd_in;
	int		fd_out;
}	t_cmd_info;	

// モジュール外部から使う関数の宣言を行う

t_cmd_info	*ft_cmd_info_list(char **cmds, t_env_info *env_info_p);
char		**ft_gen_cmds(char *cmd);


#endif