/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:05:45 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/02 20:30:43 by rkitao           ###   ########.fr       */
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
# include <fcntl.h>
# include <signal.h>
# include <linux/limits.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

extern volatile sig_atomic_t	g_signum;


void	ft_free_array(char **array);
void	ft_show_all(char **array);
int		ft_array_len(char **array);
char	**ft_add_str(char **array, char *str);
int		ft_status_code(int flag, int new_status);


#endif