/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:48:53 by yyamasak          #+#    #+#             */
/*   Updated: 2024/07/14 19:26:49 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <linux/limits.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

static  int count_args(char **argv)
{
    int num;

    num = 0;
    while (argv[num])
        num++;
    return (num);
}

// {cd PATH}で動くが{cd}のみで来た場合は動かさない方針で
void    ft_cd(char **argv)
{
    int		argc;
	char	*dir_name;

    argc = count_args(argv);
	if (argc < 2)
		return ;
	dir_name = argv[1];
    if (argc > 2)
	{
		printf("cd: too many arguments\n");
		errno = 1;
	}
	else if (chdir(dir_name) == -1)
		printf("cd: %s: %s\n", dir_name, strerror(errno));
}

// int main(int ac, char **av)
// {
//     char pathname[PATH_MAX];

//     ft_cd(av);
//     getcwd(pathname, PATH_MAX);
//     fprintf(stdout,"現在のファイルパス:%s\n", pathname);
// }