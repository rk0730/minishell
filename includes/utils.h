/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:05:45 by rkitao            #+#    #+#             */
/*   Updated: 2024/11/14 14:06:36 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <linux/limits.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

#ifdef RKITAO_DEBUG
# define RKITAO(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
# define RKITAO(fmt, ...)
#endif
#ifdef YYAMASAK_DEBUG
# define YYAMASAK(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
# define YYAMASAK(fmt, ...)
#endif

extern volatile sig_atomic_t	g_signum;


typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

void	ft_free_array(char **array);
void	ft_show_all(char **array);
int		ft_array_len(char **array);
char	**ft_add_str(char **array, char *str);
int		ft_status_code(int flag, int new_status);
char	*ft_join_free(char *s1, char *s2);

int		ft_close(int fd, int flag);

#endif