/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:04:09 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/01 11:15:30 by kitaoryoma       ###   ########.fr       */
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
}	t_env_pair;

typedef struct s_env_info
{
	t_env_pair	*env_list;
	// int			last_status; statusはcmdのint	ft_status_code(int flag, int new_status)で管理する
	char		*input;//ヒアドクなども含めた入力　環境変数ではないが都合がいいのでここに入れる
	int			input_fd;//同上
}	t_env_info;

t_env_pair	*ft_gen_env_list(char **envp);
char		**ft_gen_path_array(t_env_pair *env_list);
void		ft_show_env_list(t_env_pair *env_list);
char		*ft_search_env(char *search, t_env_pair *env_list);
char		**ft_gen_cmd_env(t_env_pair *env_list);

#endif