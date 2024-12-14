/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:04:09 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 18:29:57 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "utils.h"

typedef struct s_env_pair
{
	char				*key;
	char				*value;
	struct s_env_pair	*next;
}						t_env_pair;

typedef struct s_env_info
{
	t_env_pair			*env_list;
	char				*input;
}						t_env_info;

enum					e_export_mode
{
	REPLACE = 0,
	ADD = 1
};

t_env_pair				*ft_gen_env_list(char **envp);
char					**ft_gen_path_array(t_env_pair *env_list);
void					ft_free_env_list(t_env_pair *env_list);
void					ft_show_env_list(t_env_pair *env_list);
char					*ft_search_env(char *search, t_env_pair *env_list);
t_env_pair				*ft_search_env_node(char *search, t_env_pair *env_list);
char					**ft_gen_cmd_env(t_env_pair *env_list);
void					ft_add_env_list(t_env_pair **env_list_p,
							t_env_pair *new);
void					ft_update_env_list(t_env_pair **env_list_p,
							t_env_pair *new, int mode);
void					ft_show_env_list(t_env_pair *env_list);
void					ft_show_env_list2(t_env_pair *env_list);

#endif