/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:35:55 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/12 16:44:19 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "cmd.h"
#include "env.h"

static int	ft_is_valid_envnm(char *s, int len)
{
	int	i;
	int	is_all_num;

	i = 0;
	is_all_num = 0;
	while (i < len)
	{
		if (!(ft_isalpha(s[i]) || s[i] == '_') && i == 0)
			return (0);
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		if (ft_isalpha(s[i]) || s[i] == '_')
			is_all_num = 1;
		i++;
	}
	return (is_all_num);
}

t_env_pair	*ft_new_env2(char *key, char *value)
{
	t_env_pair	*env_pair;

	env_pair = (t_env_pair *)malloc(sizeof(t_env_pair));
	if (!env_pair)
		return (NULL);
	env_pair->key = key;
	env_pair->value = value;
	env_pair->next = NULL;
	return (env_pair);
}

static int	ft_add_env_process(t_env_pair *env_list, char *str, int key_len,
		int mode)
{
	t_env_pair	*new;
	char		*key;
	char		*value;

	if (mode == -1)
	{
		key = ft_strdup(str);
		value = NULL;
	}
	else
	{
		key = ft_substr(str, 0, key_len - mode);
		value = ft_substr(str, key_len + 1, ft_strlen(str) - key_len - 1);
	}
	new = ft_new_env2(key, value);
	if (ft_search_env_node(new->key, env_list) && (new->value))
		ft_update_env_list(&env_list, new, mode);
	else if (!ft_search_env_node(new->key, env_list))
		ft_add_env_list(&env_list, new);
	return (0);
}

static int	ft_setenv(t_env_pair *env_list, char *str)
{
	char	*equal_pos;
	int		plus_flg;

	equal_pos = ft_strchr(str, '=');
	plus_flg = 0;
	if (!equal_pos)
	{
		if (!ft_is_valid_envnm(str, ft_strlen(str)))
			return (1);
		return (ft_add_env_process(env_list, str, ft_strlen(str), -1));
	}
	if (equal_pos - str == 1 && *str == '_')
		return (0);
	if (ft_strchr(str, '+') == equal_pos - 1)
		plus_flg = 1;
	if (!ft_is_valid_envnm(str, equal_pos - str - plus_flg))
		return (1);
	return (ft_add_env_process(env_list, str, equal_pos - str, plus_flg));
}

int	ft_export(t_cmd_info cmd_info, t_env_info env_info)
{
	int	i;
	int	status;
	int	return_st;

	i = 1;
	status = 0;
	while (cmd_info.cmd_argv[i])
	{
		return_st = ft_setenv(env_info.env_list,
				cmd_info.cmd_argv[i]);
		if (return_st == 1)
			ft_printf_fd(STDERR_FILENO,
				"export: `%s': not a valid identifier\n", cmd_info.cmd_argv[i]);
		status |= return_st;
		i++;
	}
	if (i == 1)
		ft_show_env_list2(env_info.env_list);
	return (status);
}
