/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:36:56 by rgolfett          #+#    #+#             */
/*   Updated: 2024/01/05 18:18:32 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
ssize_t	ft_args(char *str, ssize_t i, va_list args, ssize_t cmp);
ssize_t	ft_hex(unsigned long nb, ssize_t cmp);
ssize_t	ft_majxhex(long nb, ssize_t cmp);
ssize_t	ft_int(int nb, ssize_t cmp);
ssize_t	ft_unsigned(unsigned int nb, ssize_t cmp);
ssize_t	ft_sargs(va_list args, ssize_t cmp);
ssize_t	ft_pargs(va_list args, ssize_t cmp);
ssize_t	ft_iargs(va_list args, ssize_t cmp);
ssize_t	ft_xargs(va_list args, ssize_t cmp);
ssize_t	ft_majxargs(va_list args, ssize_t cmp);
size_t	ft_strlen(const char *str);
ssize_t	ft_char(int c, ssize_t cmp);
int		ft_intsign(int nb, int cmp);
char	*ft_put(int m, char *tab, int i);
char	*ft_majxput(int m, char *tab, int i);
ssize_t	ft_uargs(va_list args, ssize_t cmp);
ssize_t	ft_dchar(char c, ssize_t cmp);
int		ft_zero(ssize_t cmp);

#endif