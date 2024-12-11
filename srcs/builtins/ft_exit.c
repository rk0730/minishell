/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:50:11 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/11 12:24:36 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_help2(char *str, int sign)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	if (len > 19 || len == 0)
		return (-1);
	if (len == 19)
	{
		if (sign == 1 && ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (-1);
		else if(sign == -1 && ft_strncmp(str, "9223372036854775808", 19) > 0)
			return (-1);
	}
	return (0);
}

// longの範囲内なら256で割ったあまりを返す　範囲外なら-1を返す
static int	ft_exit_help(char *str)
{
	int	i;
	int	sign;
	int	result;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (ft_help2(str, sign) == -1)
		return (-1);
	result = 0;
	i = 0;
	while (str[i])
		result = (unsigned char)(result * 10 + str[i++] - '0');
	result = (unsigned char)(result * sign);
	return (result);
}

static int	ft_exec_exit(t_cmd_info cmd_info, int result, int read_pipe, int write_pipe)
{
	// long範囲外か数値でなければエラーを表示して終了する
	if (result == -1)
	{
		ft_printf_fd(STDERR_FILENO, "exit: %s: numeric argument required\n", cmd_info.cmd_argv[1]);
		// パイプがない時はexit パイプがある時はreturn	
		if (read_pipe == -1 && write_pipe == -1)
		{
			printf("exit\n");
			exit(2);
		}
		return 2;
	}
	else
	{
		// 2つ目の引数があればエラー
		if (cmd_info.cmd_argv[2] != NULL)
		{
			ft_printf_fd(STDERR_FILENO, "exit: too many arguments\n");
			return (CMD_ERROR);
		}
		// パイプがない時はexit パイプがある時はreturn
		if (read_pipe == -1 && write_pipe == -1)
		{
			printf("exit\n");
			exit(result);
		}
		return result;
	}
}

int	ft_exit(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe)
{
	int		result;
	char	*trim;

	(void)env_info;
	ft_choose_fd(cmd_info, read_pipe, write_pipe, FALSE);
	ft_close(env_info.std_in, 8);
	ft_close(env_info.std_out, 9);
	if (cmd_info.cmd_argv[1] == NULL)
	{
		// パイプがない時はexit パイプがある時はreturn
		if (read_pipe == -1 && write_pipe == -1)
		{
			printf("exit\n");
			exit(ft_status_code(0, 0));
		}
		return (ft_status_code(0, 0));
	}
	// 前後の空白を除く
	trim = ft_strtrim(cmd_info.cmd_argv[1], " ");
	result = ft_exit_help(trim);
	free(trim);
	return (ft_exec_exit(cmd_info, result, read_pipe, write_pipe));
}
