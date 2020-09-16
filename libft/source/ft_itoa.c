/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:50:55 by kroselin          #+#    #+#             */
/*   Updated: 2020/09/16 15:27:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	ft_nb_len(long nb)
{
	size_t len;

	len = 0;
	if (nb < 0)
	{
		nb *= (-1);
		len++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	if (nb < 10)
	{
		nb = nb % 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char		*str;
	long int	nb;
	size_t		i;

	nb = n;
	i = ft_nb_len(nb);
	if (!(str = ft_memalloc(i + 1)))
		return (0);
	str[i--] = '\0';
	if (nb == 0)
		str[0] = 0 + '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= (-1);
	}
	while (nb > 0)
	{
		str[i] = '0' + (nb % 10);
		nb = nb / 10;
		i--;
	}
	return (str);
}
