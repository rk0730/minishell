/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:21:06 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/08/04 17:21:33 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.h"

char	*ft_join_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}
