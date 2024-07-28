/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdinfo_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:12:39 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/28 15:05:23 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_cmd_info	*ft_cmd_info_list(char **cmds, t_env_info *env_info_p)
{
	t_cmd_info	*cmd_list;
	char		**tokens;
	// int			redirect_err;
	int i;

	cmd_list = (t_cmd_info *)malloc(sizeof(t_cmd_info) * ft_array_len(cmds));
	if (!cmd_list)
		exit(EXIT_FAILURE);
	// リダイレクトエラーがないか確認する
	i = 0;
	// redirect_err = 0;
	while (i < ft_array_len(cmds))
	{
		tokens = ft_gen_tokens(cmds[i]);
		if (ft_redirect_err(tokens) == 1)
		{
			ft_free_array(tokens);
			return (NULL);
			// redirect_err = 1;
		}
		ft_free_array(tokens);
		i++;
	}
	i = 0;
	while (i < ft_array_len(cmds))
	{
		tokens = ft_gen_tokens(cmds[i]);
		cmd_list[i].fd_in = ft_heredoc(tokens, env_info_p);
		ft_free_array(tokens);
		i++;
	}
	// // リダイレクトエラー
	// if (redirect_err == 1)
	// {
	// 	free(cmd_list);
	// 	return (NULL);
	// }
	// 最後の文字がリダイレクト記号
	tokens = ft_gen_tokens(cmds[ft_array_len(cmds) - 1]);
	if (ft_is_last_redirect(tokens))
	{
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
		ft_free_array(tokens);
		return (NULL);
	}
	i = 0;
	while (i < ft_array_len(cmds))
	{
		tokens = ft_gen_tokens(cmds[i]);
		ft_in_out_fd(tokens, *env_info_p, &(cmd_list[i]), cmd_list[i].fd_in);
		cmd_list[i].cmd_argv = ft_gen_cmd_argv(tokens, *env_info_p);
		ft_free_array(tokens);
		i++;
	}
	return (cmd_list);
}