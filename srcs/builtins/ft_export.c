#include "builtins.h"
#include "env.h"

t_env_pair	*ft_search_env_node(char *search, t_env_pair *env_list)
{
	t_env_pair	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, search, ft_strlen(tmp->key)+1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

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

static void	ft_update_env_list(t_env_pair **env_list_p, t_env_pair *new)
{
	t_env_pair	*node;

	if (!new)
		return ;
	if (!*env_list_p)
	{
		*env_list_p = new;
		return ;
	}
	node = ft_search_env_node(new->key, *env_list_p);
	node->value = new->value;
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

static  int ft_setenv(t_env_pair *env_list, char *str)
{
	t_env_pair	*new;

	new = ft_new_env(str);
	// printf("new key: %s new value: %s\n", new->key, new->value);
	if (ft_search_env_node(new->key, env_list) && *(new->value))
		ft_update_env_list(&env_list, new);
	if (!ft_search_env_node(new->key, env_list))
		ft_add_env_list(&env_list, new);
	return (0);
}

int		ft_export(t_cmd_info cmd_info, t_env_info env_info)
{
    int i;
    int status;

    i = 1;
    while (cmd_info.cmd_argv[i])
	{
		// printf("this node will change: %s\n", cmd_info.cmd_argv[i]);
        status |= ft_setenv(env_info.env_list, cmd_info.cmd_argv[i++]);
	}
    return (status);
}