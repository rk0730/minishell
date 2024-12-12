#include "builtins.h"
#include "env.h"

void	refresh_node(t_env_pair *node)
{
	if (!node)
		return ;
	// printf("%s=%s\n", node->key, node->value);
	RKITAO("%s=%s\n", node->key, node->value);
	if (node->key)
	{
		free(node->key);
		node->key = NULL;
	}
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	if (node)
	{
		free(node);
		node = NULL;
	}
}

static int	ft_delenv(t_env_pair **env_list, char *key)
{
	t_env_pair	*tmp;
	t_env_pair	*prev;

	tmp = *env_list;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			if (prev == NULL)
				*env_list = tmp->next;
			else
				prev->next = tmp->next;
			// TODO fix segumentation fault when following condition: unset SHELL
			refresh_node(tmp);
			break ;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (0);
}

int	ft_unset(t_cmd_info cmd_info, t_env_info *env_info_p)
{
	int i;
	int status;

	i = 1;
	status = 0;
	while (cmd_info.cmd_argv[i])
	{
		// printf("this node will change: %s\n", cmd_info.cmd_argv[i]);
		if (ft_strncmp(cmd_info.cmd_argv[i], "_", 2) != 0)
			status |= ft_delenv(&(env_info_p->env_list), cmd_info.cmd_argv[i]);
		i++;
	}
	return (status);
}