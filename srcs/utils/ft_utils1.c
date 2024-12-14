/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:19:50 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 13:29:18 by yyamasak         ###   ########.fr       */
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
		RKITAO("array[%d]: [%s]\n", i, array[i]);
		YYAMASAK("array[%d]: [%s]\n", i, array[i]);
		i++;
	}
	RKITAO("array[%d]: [%s]\n", i, array[i]);
	YYAMASAK("array[%d]: [%s]\n", i, array[i]);
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

int	ft_close(int fd, int flag)
{
	if (fd >= 0)
		return (close(fd));
	else
		return (-1);
}
