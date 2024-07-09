/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:55:05 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/09 11:42:34 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cmdモジュールで作った関数のうち、外部に公開するもののみここで宣言する

//cmdモジュールはコマンドの実行に関する関数を集めたモジュールである

#ifndef CMD_H
# define CMD_H

# include "utils.h"

enum e_cmd_error
{
	CMD_ERROR = 1,
	CMD_NOT_FOUND = 127,
};

void	ft_exec_cmd(char *cmd, char **path_array);

#endif