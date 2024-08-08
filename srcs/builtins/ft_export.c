#include "builtins.h"
#include "env.h"

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

static  int ft_setenv(t_env_pair *env_list, char *str)
{
	t_env_pair	*new;

	new = ft_new_env(str);
	ft_add_env_list(&env_list, new);
	return (0);
}

int		ft_export(t_cmd_info cmd_info, t_env_info env_info)
{
    int i;
    int status;

    i = 1;
    while (cmd_info.cmd_argv[i])
        status |= ft_setenv(env_info.env_list, cmd_info.cmd_argv[i++]);
    return (status);
}