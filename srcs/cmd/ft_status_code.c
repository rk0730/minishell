/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:42:27 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/28 18:47:19 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	ft_status_code(int flag, int new_status)
{
	static int	status = 0;

	if (flag)
	{
		status = new_status;
		return (status);
	}
	else
		return (status);
}
