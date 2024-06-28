/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:08:56 by rkitao            #+#    #+#             */
/*   Updated: 2024/06/06 17:24:31 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf_fd(int fd, const char *format, ...);
int	ft_printf(const char *format, ...);
int	ft_formats(int fd, char fmt, va_list *arg);
int	ft_convert_c(int fd, char c);
int	ft_convert_s(int fd, char *str);
int	ft_convert_d(int fd, int num);
int	ft_convert_i(int fd, int num);
int	ft_convert_u(int fd, unsigned int num);
int	ft_convert_p(int fd, void *address);
int	ft_convert_x(int fd, unsigned int num);
int	ft_convert_x2(int fd, unsigned int num);

#endif
