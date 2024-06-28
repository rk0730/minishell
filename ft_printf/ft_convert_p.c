/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:36:15 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/06/06 17:03:07 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert_p_h(int fd, unsigned long long num, int res)
{
	int	tmp;

	if (res == -1)
		return (-1);
	if (num >= 16)
	{
		tmp = ft_convert_p_h(fd, num / 16, res);
		if (tmp == -1)
			return (-1);
		else
			res += tmp;
	}
	tmp = ft_convert_c(fd, "0123456789abcdef"[num % 16]);
	if (tmp == -1)
		return (-1);
	else
		return (res + tmp);
}

int	ft_convert_p(int fd, void *address)
{
	unsigned long long	num;
	int					res;

	num = (unsigned long long)address;
	res = 0;
	if (write(fd, "0x", 2) == -1)
		return (-1);
	else
		res += 2;
	res += ft_convert_p_h(fd, num, 0);
	return (res);
}
