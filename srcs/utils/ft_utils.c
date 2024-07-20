/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:07:33 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/20 14:12:18 by rkitao           ###   ########.fr       */
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