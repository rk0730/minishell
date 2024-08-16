#include "builtins.h"
#include "env.h"

static  int ft_delenv(t_env_pair **env_list, char *key)
{
    t_env_pair *tmp;
    t_env_pair *prev;

    tmp = *env_list;
    prev = NULL;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + 1) == 0)
            break;
        prev = tmp;
        tmp = tmp->next;
    }
    if (!tmp)
        return (0);
    if (prev)
        prev->next = tmp->next;
    else
        *env_list = tmp->next; 
    free(tmp->key);
    free(tmp->value);
    free(tmp);
    return (0);
}


int ft_unset(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe)
{
    int i;
    int status;

    i = 1;
	ft_choose_fd(cmd_info, read_pipe, write_pipe);
    while (cmd_info.cmd_argv[i])
	{
		// printf("this node will change: %s\n", cmd_info.cmd_argv[i]);
        status |= ft_delenv(&(env_info.env_list), cmd_info.cmd_argv[i++]);
	}
    return (status);
}