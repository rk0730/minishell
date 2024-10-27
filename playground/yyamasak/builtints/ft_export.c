#include "builtins.h"

int		ft_export(t_cmd_info cmd_info, t_env_info env_info)
{
    for(int i=0; cmd_info.cmd_argv[i]; i++)
        printf("%s\n", cmd_info.cmd_argv[0]);
    return (0);
}