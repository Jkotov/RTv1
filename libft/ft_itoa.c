/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:52:09 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	size_t	int_len(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char	*s;
	size_t	len;
	int		flag;

	len = int_len(n);
	flag = 1;
	if (n < 0)
	{
		len++;
		flag = -1;
	}
	s = ft_strnew(len);
	if (s == NULL)
		return (NULL);
	if (n == 0)
		*s = '0';
	while (n)
	{
		len--;
		*(s + len) = (n % 10) * flag + '0';
		n /= 10;
	}
	if (flag == -1)
		*s = '-';
	return (s);
}
