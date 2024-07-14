/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:27:26 by yyamasak          #+#    #+#             */
/*   Updated: 2024/07/14 17:43:39 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	ft_pwd()
{
	char *pathname[PATH_MAX];

	getcwd(pathname, PATH_MAX);
	ft_printf("%s\n", pathname);
}