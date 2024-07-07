/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:04:09 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/07 18:06:49 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//envモジュールで作った関数のうち、外部に公開するもののみここで宣言する

//envモジュールは環境変数に関する関数を集めたモジュールである


#ifndef ENV_H
# define ENV_H

# include "utils.h"


t_env_pair	**ft_gen_env_list(char **envp);
char	**ft_gen_path_array(t_env_pair **env_list);

#endif