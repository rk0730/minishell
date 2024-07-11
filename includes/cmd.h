/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:55:05 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/11 20:18:06 by kitaoryoma       ###   ########.fr       */
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
};

enum e_token_status
{
	NORMAL,
	SINGLE_QUOTE,//'が足りない
	DOUBLE_QUOTE,//"が足りない
	REDIRECT,// >>>や<<<,<>など不適なリダイレクト
};

void	ft_exec_cmd(char *cmd, char **path_array);

//臨時で追加
char	**ft_gen_tokens(char *input);

#endif