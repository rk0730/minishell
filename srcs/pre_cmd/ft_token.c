/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:48:51 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/13 15:39:17 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

// static int	_ft_next_token_h2(char *input, int i)
// {
// 	while (input[i] == '>' || input[i] == '<')
// 		i++;
// 	return (i);
// }

// iをクォーテーションcの中身の次の文字に移動させる　token_statusにはクォーテーションの種類を入れる
int	_ft_skip_quotation(char *input, int i, int *token_status, char c)
{
	i++;
	while (input[i] != '\0' && input[i] != c)
		i++;
	if (input[i] != '\0')
		i++;
	else
	{
		if (token_status != NULL)
		{
			if (c == '\'')
				*token_status = SINGLE_QUOTE;
			else
				*token_status = DOUBLE_QUOTE;
		}
	}
	return (i);
}

// iを次のトークンの先頭に移動させる
static int	_ft_next_token(char *in, int i, int *token_status)
{
	if (in[i] == '>' || in[i] == '<')
	{
		while (in[i] == '>' || in[i] == '<')
			i++;
		return (i);
		// return (_ft_next_token_h2(in, i));
	}
	while (in[i] != '\0' && in[i] != ' ' && in[i] != '<' && in[i] != '>')
	{
		if (in[i] == '\'')
			i = _ft_skip_quotation(in, i, token_status, '\'');
		else if (in[i] == '\"')
			i = _ft_skip_quotation(in, i, token_status, '\"');
		else
		{
			while (in[i] && in[i] != ' ' && in[i] != '\'' && in[i] != '\"'
				&& in[i] != '<' && in[i] != '>')
				i++;
		}
	}
	return (i);
}

// tokenの数を数える
static int	_ft_count_tokens(char *input, int *token_status)
{
	int	count;
	int	iter;

	count = 0;
	iter = 0;
	while (input[iter] != '\0' && input[iter] == ' ')
		iter++;
	while (input[iter])
	{
		iter = _ft_next_token(input, iter, token_status);
		count++;
		while (input[iter] != '\0' && input[iter] == ' ')
			iter++;
	}
	return (count);
}

// 文字列を抽出してtokensに入れる
static void	_ft_gen_tokens_h(char **tokens, char *input, int len)
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
		end = _ft_next_token(input, iter, NULL);
		tokens[num] = ft_substr(input, iter, end - iter);
		while (input[end] != '\0' && input[end] == ' ')
			end++;
		iter = end;
		num++;
	}
	tokens[num] = NULL;
}

// トークン：基本的には空白で区切られた文字列。
// ただし、クォーテーションで囲まれた文字列は全体で1トークン 
// リダイレクト記号なども1トークン　パイプの分割はすでに終わっている
// トークンを生成する関数　クォーテーションエラーがある場合はNULLを返す　他のエラーはここでは見逃す
char	**_ft_gen_tokens(char *input)
{
	int		token_status;
	char	**tokens;
	int		len;

	token_status = NORMAL;
	len = _ft_count_tokens(input, &token_status);
	if (token_status != NORMAL)
		return (NULL);
	tokens = (char **)malloc(sizeof(char *) * (len + 1));
	if (tokens == NULL)
		exit(EXIT_FAILURE);
	_ft_gen_tokens_h(tokens, input, len);
	return (tokens);
}
