/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:07:33 by rkitao            #+#    #+#             */
/*   Updated: 2024/11/11 22:55:55 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_show_all(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("array[%d]: %s\n", i, array[i]);
		i++;
	}
}

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**ft_add_str(char **array, char *str)
{
	char	**new_array;
	int		i;

	new_array = (char **)malloc(sizeof(char *) * (ft_array_len(array) + 2));
	i = 0;
	while (array[i])
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = str;
	new_array[i + 1] = NULL;
	free(array);
	return (new_array);
}

// flagはデバックでつけたもの
int ft_close(int fd, int flag){
	// printf("%d at %d, close fd: %d\n", flag, getpid(), fd);
	if (fd >= 0)
		return (close(fd));
	else
		return (-1);
}
