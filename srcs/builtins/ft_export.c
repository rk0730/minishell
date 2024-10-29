#include "builtins.h"
#include "env.h"

// to do: create test case
static	int	ft_is_valid_envnm(char *s, int len)
{
	int	i;
	int	is_all_num;

	i = 0;
	is_all_num = 0;
	while (i < len)
	{
		if (!(ft_isalpha(s[i]) || s[i] == '_') && i == 0)
			return (0);
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		if (ft_isalpha(s[i]) || s[i] == '_')
			is_all_num = 1;
		i++;
	}
	return (is_all_num);
}
static t_env_pair	*ft_search_env_node(char *search, t_env_pair *env_list)
{
	t_env_pair	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, search, ft_strlen(tmp->key)+1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static t_env_pair	*ft_new_env(char *key, char *value)
{
	t_env_pair	*env_pair;

	env_pair = (t_env_pair *)malloc(sizeof(t_env_pair));
	if (!env_pair)
		return (NULL);
	env_pair->key = key;
	env_pair->value = value;
	env_pair->next = NULL;
	return (env_pair);
}

// mode 0: replace, 1: add
// newのkeyとnew自身はfreeされる
void	ft_update_env_list(t_env_pair **env_list_p, t_env_pair *new, int mode)
{
	t_env_pair	*node;
	char		*tmp;

	if (!new)
		return ;
	if (!*env_list_p)
	{
		*env_list_p = new;
		return ;
	}
	node = ft_search_env_node(new->key, *env_list_p);
	free(new->key);
	if (mode == 0)
	{
		free(node->value);
		node->value = new->value;
	}
	else
	{
		tmp = ft_strjoin(node->value, new->value);
		free(new->value);
		free(node->value);
		node->value = tmp;
	}
	// TODO considering why segumentation fault if free new variable
	// ここは、もしかしたらsubstrの部分で問題かもしれない。export作り直した方がはやそう。
	// free(new);
}

static void	ft_add_env_list(t_env_pair **env_list_p, t_env_pair *new)
{
	t_env_pair	*last;

	if (!new)
		return ;
	if (!*env_list_p)
	{
		*env_list_p = new;
		return ;
	}
	last = *env_list_p;
	while (last->next)
		last = last->next;
	last->next = new;
}

static  int ft_setenv(t_env_pair *env_list, char *str)
{
	t_env_pair	*new;
	char		*e_pos;
	char		*key;
	char		*value;
	int			plus_flg;

	e_pos = ft_strchr(str, '=');
	plus_flg = REPLACE;
	// =がない場合で変数名に禁足文字ない場合と変数名が上書きできない_の場合
	if ((!e_pos && ft_is_valid_envnm(str, ft_strlen(str))) ||(e_pos - str == 1 && *str == '_'))
		return (0);
	if (!e_pos)
		return (2);
	// 変数名に禁足文字ある場合
	if (ft_strchr(str, '+') == e_pos - 1)
		plus_flg = ADD;
	key = ft_substr(str, 0, e_pos - str - plus_flg);
	if (!ft_is_valid_envnm(key, e_pos - str - plus_flg))
		return (2);
	value = ft_substr(str, e_pos - str + 1, str + ft_strlen(str) - e_pos - 1);
	new = ft_new_env(key, value);
	//  not forget to free
	if (!(new))
		return (1);
	// printf("new key: %s new value: %s\n", new->key, new->value);
	if (ft_search_env_node(new->key, env_list) && *(new->value))
		ft_update_env_list(&env_list, new, plus_flg);
	if (!ft_search_env_node(new->key, env_list))
		ft_add_env_list(&env_list, new);
	return (0);
}

int		ft_export(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe)
{
    int i;
    int status;
	int return_st;

    i = 1;
	ft_choose_fd(cmd_info, read_pipe, write_pipe);
	status = 0;
    while (cmd_info.cmd_argv[i])
	{
		// printf("this node will change: %s\n", cmd_info.cmd_argv[i]);
        return_st = ft_setenv(env_info.env_list, cmd_info.cmd_argv[i]);
		if (return_st == 2) 
		{
			ft_printf_fd(STDERR_FILENO, "export: `%s': not a valid identifier\n", cmd_info.cmd_argv[i]);
			return_st = 1;
		}
		status |= return_st;
		i++;
	}
    return (status);
}