/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:30:49 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/04/28 18:41:41 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*result;

	if (size != 0 && SIZE_MAX / size < count)
	{
		return (NULL);
	}
	result = malloc(count * size);
	if (!result)
	{
		return (NULL);
	}
	ft_bzero(result, count * size);
	return (result);
}
