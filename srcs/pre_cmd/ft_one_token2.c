/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_token2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:09:42 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 18:17:01 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

// array1のlen1個とarray2のlen2個をつなげる
char	**_ft_join_array(char **array1, char **array2, int len1, int len2)
{
	char	**new_array;
	int		i;

	new_array = (char **)malloc(sizeof(char *) * (len1 + len2 + 1));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		new_array[i] = array1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		new_array[i] = array2[i - len1];
		i++;
	}
	new_array[i] = NULL;
	free(array1);
	free(array2);
	return (new_array);
}

char	*_ft_help_one_token(char *token, t_env_info env_info, int *utils,
		char *now)
{
	char	*tmp;

	utils[2] = utils[1];
	while (token[utils[2]] && token[utils[2]] != '\''
		&& token[utils[2]] != '\"')
		utils[2]++;
	if (token[utils[2] - 1] == '$' && (token[utils[2]] == '\''
			|| token[utils[2]] == '\"'))
		tmp = ft_substr(token, utils[1], utils[2] - utils[1] - 1);
	else
		tmp = ft_substr(token, utils[1], utils[2] - utils[1]);
	now = ft_join_free(now, _ft_tokenize(tmp, env_info));
	free(tmp);
	return (now);
}
