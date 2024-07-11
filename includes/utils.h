/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:05:45 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/11 20:58:21 by kitaoryoma       ###   ########.fr       */
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

# include "libft.h"
# include "ft_printf.h"

// typedef struct s_env_pair
// {
// 	char				*key;
// 	char				*value;
// 	struct s_env_pair	*next;
// }	t_env_pair;

void	ft_free_array(char **array);
void	ft_show_all(char **array);
int		ft_array_len(char **array);

#endif