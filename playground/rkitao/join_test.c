#include <stdio.h>
#include "../../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct info
{
	char *history;
}	t_info;

void ft_join(t_info *info)
{
	char *tmp;

	tmp = info->history;
	printf("Before joining: %s\n", info->history);
	info->history = ft_strjoin(info->history, "aaa");
	printf("After joining: %s\n", info->history);
	free(tmp);
}

int main(void)
{
	t_info *info;

    info = (t_info *)malloc(sizeof(t_info));
	while (1)
	{
		info->history = readline("Enter a command: ");
		ft_join(info);
		printf("After joined: %s\n", info->history);
		add_history(info->history);
		if (ft_strncmp(info->history, "exit", 4) == 0)
			break;
		free(info->history);
	}
}