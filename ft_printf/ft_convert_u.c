/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:03:31 by rkitao            #+#    #+#             */
/*   Updated: 2024/06/06 17:03:38 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert_u_h(int fd, unsigned int num, int res)
{
	int	tmp;

	if (res == -1)
		return (-1);
	if (num >= 10)
	{
		tmp = ft_convert_u_h(fd, num / 10, res);
		if (tmp == -1)
			return (-1);
		else
			res += tmp;
	}
	tmp = ft_convert_c(fd, '0' + num % 10);
	if (tmp == -1)
		return (-1);
	else
		return (res + tmp);
}

int	ft_convert_u(int fd, unsigned int num)
{
	return (ft_convert_u_h(fd, num, 0));
}
