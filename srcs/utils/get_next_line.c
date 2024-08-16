
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:33:41 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/05/11 00:36:00 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_count_word(char *str, size_t *start_p, size_t *end_p)
{
	*start_p = 0;
	while (*start_p < (size_t)BUFFER_SIZE && str[*start_p] == '\0')
		*start_p = *start_p + 1;
	*end_p = *start_p;
	while (*end_p < (size_t)BUFFER_SIZE)
	{
		if (str[*end_p] != '\0' && str[*end_p] != '\n')
			*end_p = *end_p + 1;
		else
			break ;
	}
	if (str[*end_p] == '\n')
		*end_p = *end_p + 1;
}

char	*ft_gen_ans_h(char *box[FOPEN_MAX + 1], int fd, char **ap, size_t *se)
{
	int	read_r;

	while (se[1] == (size_t)BUFFER_SIZE && ft_find_nl(*ap) == 0)
	{
		read_r = read(fd, box[fd], BUFFER_SIZE);
		if (read_r == -1)
		{
			free(*ap);
			ft_free_null(box);
			return (NULL);
		}
		if (read_r == 0)
		{
			free(box[fd]);
			box[fd] = NULL;
			return (*ap);
		}
		if (ft_gen_help(box[fd], ap, se) == 1)
		{
			ft_free_null(box);
			return (NULL);
		}
	}
	return (*ap);
}

int	ft_gen_help(char *buf, char **ans_p, size_t *start_end)
{
	ft_count_word(buf, &(start_end[0]), &(start_end[1]));
	*ans_p = ft_join_ans(ans_p, buf, start_end);
	if (!(*ans_p))
		return (1);
	while (start_end[0] < start_end[1])
	{
		if (buf)
			buf[start_end[0]] = '\0';
		start_end[0] = start_end[0] + 1;
	}
	return (0);
}

char	*ft_gen_ans(int fd, char *box[FOPEN_MAX + 1])
{
	size_t	start_end[2];
	char	*ans;
	int		result;

	ans = (char *)malloc(sizeof(char));
	if (!ans)
	{
		ft_free_null(box);
		return (NULL);
	}
	*ans = '\0';
	result = ft_gen_help(box[fd], &ans, start_end);
	if (result == 1)
	{
		ft_free_null(box);
		return (NULL);
	}
	return (ft_gen_ans_h(box, fd, &ans, start_end));
}

char	*get_next_line(int fd)
{
	static char	*box[FOPEN_MAX + 1];
	char		*ans;
	size_t		i;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (box[fd] == NULL)
	{
		box[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(box[fd]))
		{
			ft_free_null(box);
			return (NULL);
		}
		i = 0;
		while (i < BUFFER_SIZE + 1)
			box[fd][i++] = '\0';
	}
	ans = ft_gen_ans(fd, box);
	if (!ans || ft_strlen(ans) == 0)
	{
		free(ans);
		return (NULL);
	}
	return (ans);
}
