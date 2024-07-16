//以下はft_search_env.cの内容


// searchという環境変数が見つかったらそのvalueを返す
// char	*ft_search_env(char *search, t_env_pair **env_list)
// {
// 	t_env_pair *tmp;

// 	tmp = *env_list;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->key, search, ft_strlen(tmp->key)+1) == 0)
// 			return (ft_strdup(tmp->value));
// 		tmp = tmp->next;
// 	}
// 	return (ft_strdup(""));
// }



//以下はft_cmd_array.cの内容

// strの環境変数を展開した文字列を返す
// static char	*ft_expand_env(char *str, t_env_pair **env_list)
// {
// 	char	*result;
// 	char	*tmp;
// 	char	*before;
// 	int		i;
// 	int		end;

// 	result = ft_strdup("");
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$')
// 		{
// 			end = i;
// 			while (str[end] != '\0' && str[end] != ' ' && str[end] != '\"' && str[end] != '\'')
// 				end++;
// 			tmp = ft_search_env(ft_substr(str, i + 1, end - i - 1), env_list);
// 			printf("%s\n", ft_substr(str, i + 1, end - i - 1));
// 			printf("%s\n", tmp);
// 		}
// 		else
// 		{
// 			end = i;
// 			while (str[end] != '\0' && str[end] != '$')
// 				end++;
// 			tmp = ft_substr(str, i, end - i);
// 		}
// 		before = result;
// 		result = ft_strjoin(before, tmp);
// 		free(before);
// 		free(tmp);
// 		i = end;
// 	}
// 	return (result);
// }


// tokenの各文字列が"で挟まれていたら環境変数展開したり、'で挟まれていたらそれを除く（リダイレクトは飛ばす）
// char	**ft_gen_cmd_array(char **tokens, t_env_pair **env_list)
// {
// 	char	**cmd_array;
// 	int		i;

// 	i = 0;
// 	cmd_array = (char **)malloc(sizeof(char *) * (ft_array_len(tokens) + 1));
// 	if (!cmd_array)
// 		return (NULL);
// 	while (tokens[i])
// 	{
// 		cmd_array[i] = ft_expand_env(tokens[i], env_list);
// 		i++;
// 	}
// 	cmd_array[i] = NULL;
// 	return (cmd_array);
// }