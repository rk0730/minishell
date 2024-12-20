/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdinfo_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:12:39 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 15:37:06 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static int _ft_heredoc_syntax_err(char **cmds)
{
	int i;
	int j;
	char **tokens;

	i = 0;
	while (i < ft_array_len(cmds))
	{
		tokens = _ft_gen_tokens(cmds[i]);
		j = 0;
		while (j < ft_array_len(tokens) - 1)
		{
			if (ft_strncmp(tokens[j], "<<", 3) == 0 && _ft_is_redirect(tokens[j + 1]))
			{
				ft_printf_fd(STDERR_FILENO, "syntax error\n");
				ft_free_array(tokens);
				return (1);
			}
			j++;
		}
		if (ft_strncmp(tokens[ft_array_len(tokens) - 1], "<<", 3) == 0)
		{
			ft_printf_fd(STDERR_FILENO, "syntax error\n");
			ft_free_array(tokens);
			return (1);
		}
		ft_free_array(tokens);
		i++;
	}
	return (0);
}

// エラーなら1を返す
static int	_ft_help1(char **cmds, t_env_info *env_info_p, t_cmd_info *cmd_list)
{
	char	**tokens;
	int		i;

	// リダイレクトエラーがないか確認する
	i = 0;
	while (i < ft_array_len(cmds))
	{
		tokens = _ft_gen_tokens(cmds[i]);
		if (_ft_redirect_err(tokens) == 1)
		{
			// リダイレクトエラーがあった場合はヒアドクを実行して終了
			cmd_list[i].fd_in = _ft_heredoc(tokens, env_info_p);
			ft_close(cmd_list[i].fd_in, 16);
			ft_free_array(tokens);
			return (1);
		}
		ft_free_array(tokens);
		i++;
	}
	return (0);
}

// エラーなら1を返す
static int	_ft_help2(char **cmds, t_env_info *env_info_p, t_cmd_info *cmd_list)
{
	char	**tokens;
	int		i;

	// ヒアドクを実行
	i = 0;
	while (i < ft_array_len(cmds))
	{
		tokens = _ft_gen_tokens(cmds[i]);
		cmd_list[i].fd_in = _ft_heredoc(tokens, env_info_p);
		ft_free_array(tokens);
		if (g_signum == SIGINT)
			return (1);
		i++;
	}
	// 最後の文字がリダイレクト記号の場合はエラーを出して終了
	tokens = _ft_gen_tokens(cmds[ft_array_len(cmds) - 1]);
	if (_ft_is_last_redirect(tokens))
	{
		ft_printf_fd(STDERR_FILENO,
			"syntax error near unexpected token `newline'\n");
		ft_free_array(tokens);
		return (1);
	}
	ft_free_array(tokens);
	return (0);
}

// 全コマンドの情報をcmd_listというリストにして返す
t_cmd_info	*ft_cmd_info_list(char **cmds, t_env_info *env_info_p)
{
	t_cmd_info	*cmd_list;
	char		**tokens;
	int			i;

	cmd_list = (t_cmd_info *)malloc(sizeof(t_cmd_info) * ft_array_len(cmds));
	if (!cmd_list)
		exit(EXIT_FAILURE);
	// if (_ft_help1(cmds, env_info_p, cmd_list) == 1)
	// {
	// 	free(cmd_list);
	// 	return (NULL);
	// }
	// if (_ft_help2(cmds, env_info_p, cmd_list) == 1)
	// {
	// 	free(cmd_list);
	// 	return (NULL);
	// }
	// C言語のif文は必ず左からチェックし、左が真で||の場合は右を見ないので、これで上のコメントアウトと同じ処理になるはず
	if (_ft_heredoc_syntax_err(cmds) || _ft_help1(cmds, env_info_p, cmd_list) || _ft_help2(cmds, env_info_p,
			cmd_list))
	{
		free(cmd_list);
		return (NULL);
	}
	// リダイレクト処理と環境変数を展開し、cmd_argvを生成する
	i = 0;
	while (i < ft_array_len(cmds))
	{
		tokens = _ft_gen_tokens(cmds[i]);
		// RKITAO("tokens\n");
		// ft_show_all(tokens);
		_ft_in_out_fd(tokens, *env_info_p, &(cmd_list[i]), cmd_list[i].fd_in);
		cmd_list[i].cmd_argv = _ft_gen_cmd_argv(tokens, *env_info_p);
		ft_free_array(tokens);
		i++;
	}
	return (cmd_list);
}
