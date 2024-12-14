/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:18:19 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 13:27:07 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_env_pair	*ft_new_env(char *env)
{
	t_env_pair	*env_pair;

	env_pair = (t_env_pair *)malloc(sizeof(t_env_pair));
	if (!env_pair)
		return (NULL);
	env_pair->key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	env_pair->value = ft_substr(env, ft_strchr(env, '=') - env + 1, env
			+ ft_strlen(env) - ft_strchr(env, '=') - 1);
	env_pair->next = NULL;
	return (env_pair);
}

void	ft_add_env_list(t_env_pair **env_list_p, t_env_pair *new)
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

void	ft_update_env_list(t_env_pair **env_list_p, t_env_pair *new, int mode)
{
	t_env_pair	*node;
	char		*tmp;

	if (!new)
		return ;
	node = ft_search_env_node(new->key, *env_list_p);
	if (!node)
	{
		ft_add_env_list(env_list_p, new);
		return ;
	}
	else if (mode == 0)
	{
		free(new->key);
		free(node->value);
		node->value = new->value;
	}
	else
	{
		free(new->key);
		tmp = ft_join_free(node->value, new->value);
		node->value = tmp;
	}
	free(new);
}

static void	_create_default_env(t_env_pair **env_list)
{
	t_env_pair	*new;
	char		pathname[PATH_MAX];
	char		*tmp;

	new = ft_new_env("_=]");
	ft_add_env_list(env_list, new);
	new = ft_new_env("SHLVL=1");
	ft_add_env_list(env_list, new);
	new = (t_env_pair *)malloc(sizeof(t_env_pair));
	if (new)
	{
		new->key = ft_strdup("OLDPWD");
		new->value = NULL;
		if (new->key)
			ft_add_env_list(env_list, new);
	}
	getcwd(pathname, PATH_MAX);
	tmp = ft_strjoin("PWD=", pathname);
	new = ft_new_env(tmp);
	ft_add_env_list(env_list, new);
	free(tmp);
}

t_env_pair	*ft_gen_env_list(char **envp)
{
	t_env_pair	*env_list;
	t_env_pair	*new;
	int			i;

	i = 0;
	env_list = NULL;
	if (!envp || !*envp)
		_create_default_env(&env_list);
	while (envp[i])
	{
		new = ft_new_env(envp[i]);
		ft_add_env_list(&env_list, new);
		i++;
	}
	return (env_list);
}
