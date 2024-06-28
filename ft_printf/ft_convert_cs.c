/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_cs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:54:35 by rkitao            #+#    #+#             */
/*   Updated: 2024/06/06 17:01:03 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert_c(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_convert_s(int fd, char *str)
{
	int	tmp;
	int	res;

	tmp = 0;
	res = 0;
	if (str == NULL)
	{
		if (write(fd, "(null)", 6) == -1)
			return (-1);
		else
			return (6);
	}
	while (tmp != -1 && *str)
	{
		tmp = write(fd, str, 1);
		if (tmp == -1)
			return (-1);
		else
			res += tmp;
		str++;
	}
	return (res);
}
