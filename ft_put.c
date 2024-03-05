/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgolfett <rgolfett@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:46:40 by rgolfett          #+#    #+#             */
/*   Updated: 2024/03/04 14:17:50 by rgolfett         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_char(int c, ssize_t cmp)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (cmp + 1);
}

int	ft_intsign(int nb, int cmp)
{
	if (nb < 0 && nb >= -2147483647)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		return (cmp + 1);
	}
	return (cmp);
}

char	*ft_put(int m, char *tab, int i)
{
	char	*base;

	base = "0123456789abcdef";
	tab[i] = base[m];
	return (tab);
}

char	*ft_majxput(int m, char *tab, int i)
{
	char	*base;

	base = "0123456789ABCDEF";
	tab[i] = base[m];
	return (tab);
}
