/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:31:25 by rgolfett          #+#    #+#             */
/*   Updated: 2024/01/05 18:17:55 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_uargs(va_list args, ssize_t cmp)
{
	long	u;

	u = va_arg(args, long);
	cmp = ft_unsigned(u, cmp);
	return (cmp);
	return (cmp);
}

ssize_t	ft_dchar(char c, ssize_t cmp)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (cmp + 1);
}

int	ft_zero(ssize_t cmp)
{
	if (write(1, "0", 1) == -1)
		return (-1);
	return (cmp += 1);
}

ssize_t	ft_args(char *str, ssize_t i, va_list args, ssize_t cmp)
{
	if (str[i] == 'i' || str[i] == 'd')
		return (ft_iargs(args, cmp));
	else if (str[i] == 's')
		return (ft_sargs(args, cmp));
	else if (str[i] == 'p')
		return (ft_pargs(args, cmp));
	else if (str[i] == 'x')
		return (ft_xargs(args, cmp));
	else if (str[i] == 'X')
		return (ft_majxargs(args, cmp));
	else if (str[i] == 'u')
		return (ft_uargs(args, cmp));
	else if (str[i] == '%')
		return (ft_dchar('%', cmp));
	return (cmp);
}
