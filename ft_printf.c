/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:14:31 by rgolfett          #+#    #+#             */
/*   Updated: 2024/01/05 18:18:43 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_hex(unsigned long nb, ssize_t cmp)
{
	int		m;
	char	tab[16];
	int		i;

	i = 0;
	m = 0;
	if (nb == 0)
		return (ft_zero(cmp));
	while (nb >= 1)
	{
		m = nb % 16;
		nb /= 16;
		ft_put(m, tab, i);
		i++;
	}
	cmp += i;
	i--;
	while (i >= 0)
	{
		if (write(1, &tab[i], 1) == -1)
			return (-1);
		i--;
	}
	return (cmp);
}

ssize_t	ft_majxhex(long nb, ssize_t cmp)
{
	int		m;
	char	tab[16];
	int		i;

	m = 0;
	i = 0;
	if (nb == 0)
		return (ft_zero(cmp));
	while (nb >= 1)
	{
		m = nb % 16;
		nb /= 16;
		ft_majxput(m, tab, i);
		i++;
	}
	cmp += i;
	i--;
	while (i >= 0)
	{
		if (write(1, &tab[i], 1) == -1)
			return (-1);
		i--;
	}
	return (cmp);
}

ssize_t	ft_int(int nb, ssize_t cmp)
{
	int	tab[10];
	int	i;

	i = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (cmp += 11);
	}
	cmp = ft_intsign(nb, cmp);
	if (nb < 0)
		nb *= -1;
	if (nb == 0)
		return (ft_zero(cmp));
	while (nb > 0)
	{
		tab[i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	cmp += i;
	while (--i >= 0)
		if (write(1, &tab[i], 1) == -1)
			return (-1);
	return (cmp);
}

ssize_t	ft_unsigned(unsigned int nb, ssize_t cmp)
{
	int	tab[10];
	int	i;

	i = 0;
	if (nb == 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		return (cmp += 1);
	}
	while (nb > 0)
	{
		tab[i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	cmp += i;
	i--;
	while (i >= 0)
	{
		if (write(1, &tab[i], 1) == -1)
			return (-1);
		i--;
	}
	return (cmp);
}

int	ft_printf(const char *str, ...)
{
	ssize_t	cmp;
	size_t	i;
	va_list	args;

	cmp = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i +1] && str[i] == '%')
		{
			i++;
			if (str[i] == 'c')
				cmp = ft_char(va_arg(args, int), cmp);
			cmp = ft_args((char *)str, i, args, cmp);
		}
		else
			cmp = ft_dchar(str[i], cmp);
		i++;
		if (cmp == -1)
			return (va_end(args), -1);
	}
	va_end(args);
	return (cmp);
}
