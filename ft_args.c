/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:26:09 by rgolfett          #+#    #+#             */
/*   Updated: 2024/01/05 17:43:04 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_sargs(va_list args, ssize_t cmp)
{
	char	*str;

	str = va_arg(args, char *);
	if (str == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (cmp += 6);
	}
	if (write (1, str, ft_strlen(str)) == -1)
		return (-1);
	return (cmp += ft_strlen(str));
}

ssize_t	ft_pargs(va_list args, ssize_t cmp)
{
	unsigned long	ptr;

	ptr = va_arg(args, unsigned long);
	if (ptr == 0)
	{
		if (write(1, "(nil)", 5) == -1)
			return (-1);
		return (cmp += 5);
	}
	if (write(1, "0x", 2) == -1)
		return (-1);
	cmp = ft_hex(ptr, cmp);
	return (cmp += 2);
}

ssize_t	ft_iargs(va_list args, ssize_t cmp)
{
	unsigned long	i;

	i = va_arg(args, int);
	return (ft_int(i, cmp));
}

ssize_t	ft_xargs(va_list args, ssize_t cmp)
{
	unsigned long	x;

	x = va_arg(args, unsigned int );
	cmp = ft_hex(x, cmp);
	return (cmp);
}

ssize_t	ft_majxargs(va_list args, ssize_t cmp)
{
	unsigned long	majx;

	majx = va_arg(args, unsigned int);
	cmp = ft_majxhex(majx, cmp);
	return (cmp);
}
