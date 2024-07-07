/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:05:45 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/07 17:28:32 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//utilsモジュールで作ったものをここで宣言する

//utilsモジュールは他の全てのモジュールで使う汎用的な関数を集めたモジュールであり、
// 他の全てのモジュールで最初にincludeする

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

typedef struct s_env_pair
{
	char				*key;
	char				*value;
	struct s_env_pair	*next;
}	t_env_pair;

void	ft_free_array(char **array);

#endif