/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:18:19 by rkitao            #+#    #+#             */
/*   Updated: 2024/09/30 14:21:46 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// 新しい環境変数を作成する
// envには"USER=rkitao"のような文字列が入る
static t_env_pair	*ft_new_env(char *env)
{
	t_env_pair	*env_pair;

	env_pair = (t_env_pair *)malloc(sizeof(t_env_pair));
	if (!env_pair)
		return (NULL);
	env_pair->key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	env_pair->value = ft_substr(env, ft_strchr(env, '=') - env + 1, env + ft_strlen(env) - ft_strchr(env, '=') - 1);
	env_pair->next = NULL;
	return (env_pair);
}

static void	ft_add_env_list(t_env_pair **env_list_p, t_env_pair *new)
{
	t_env_pair	*last;

	if (!new)
		return ;
	if (!*env_list_p)
	{
		*env_list_p = new;
		return ;
	}
	last = *env_list_p;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_env_pair	*ft_gen_env_list(char **envp)
{
	t_env_pair	*env_list;
	t_env_pair	*new;
	int			i;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		new = ft_new_env(envp[i]);
		ft_add_env_list(&env_list, new);
		i++;
	}
	return (env_list);
}

void	ft_show_env_list(t_env_pair *env_list)
{
	t_env_pair	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
