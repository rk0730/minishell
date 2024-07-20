/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:48:51 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/07/20 20:44:47 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	ft_next_token_h2(char *input, int i, int *token_status)
{
	int	end;

	end = i;
	while (input[end] == input[i])
		end++;
	if (end - i > 2 || input[end] == '<' || input[end] == '>')
		*token_status = REDIRECT;
	return (end);
}

static int	ft_next_token_h(char *input, int i, int *token_status, char c)
{
	i++;
	while (input[i] != '\0' && input[i] != c)
		i++;
	if (input[i] != '\0')
		i++;
	else
	{
		if (c == '\'')
			*token_status = SINGLE_QUOTE;
		else
			*token_status = DOUBLE_QUOTE;
	}
	return (i);
}

static int	ft_next_token(char *in, int i, int *token_status)
{
	while (in[i] != '\0' && in[i] != ' ')
	{
		if (in[i] == '\'')
			i = ft_next_token_h(in, i, token_status, '\'');
		else if (in[i] == '\"')
			i = ft_next_token_h(in, i, token_status, '\"');
		else if (in[i] == '<' || in[i] == '>')
		{
			i = ft_next_token_h2(in, i, token_status);
			break ;
		}
		else
		{
			while (in[i] && in[i] != ' ' && in[i] != '\'' && in[i] != '\"'
				&& in[i] != '<' && in[i] != '>')
				i++;
		}
	}
	return (i);
}

static int	ft_count_tokens(char *input, int *token_status)
{
	int	count;
	int	iter;

	count = 0;
	iter = 0;
	// *token_status = NORMAL;
	while (input[iter] != '\0' && input[iter] == ' ')
		iter++;
	while (input[iter])
	{
		iter = ft_next_token(input, iter, token_status);
		count++;
		while (input[iter] != '\0' && input[iter] == ' ')
			iter++;
	}
	return (count);
}

static void	ft_gen_tokens_h(char **tokens, char *input, int len)
{
	int	num;
	int	iter;
	int	end;

	num = 0;
	iter = 0;
	while (input[iter] != '\0' && input[iter] == ' ')
		iter++;
	while (num < len)
	{
		end = ft_next_token(input, iter, NULL);
		tokens[num] = ft_substr(input, iter, end - iter);
		while (input[end] != '\0' && input[end] == ' ')
			end++;
		iter = end;
		num++;
	}
	tokens[num] = NULL;
}

char	**ft_gen_tokens(char *input)
{
	int		token_status;
	char	**tokens;
	int		len;

	token_status = NORMAL;
	len = ft_count_tokens(input, &token_status);
	if (token_status != NORMAL)
		return (NULL);
	tokens = (char **)malloc(sizeof(char *) * (len + 1));
	if (tokens == NULL)
		exit(EXIT_FAILURE);
	ft_gen_tokens_h(tokens, input, len);
	return (tokens);
}
