/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 12:05:06 by kroselin          #+#    #+#             */
/*   Updated: 2019/09/18 11:29:29 by kroselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*i1;
	const unsigned char		*i2;

	i = 0;
	i1 = (const unsigned char *)s1;
	i2 = (const unsigned char *)s2;
	while (n--)
	{
		if (i1[i] == i2[i])
			i++;
		else
			return ((int)(i1[i] - i2[i]));
	}
	return (0);
}
