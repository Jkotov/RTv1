/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:13:47 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*res;
	size_t			i;

	i = 0;
	tmp = (unsigned char*)src;
	res = (unsigned char*)dst;
	while (i < n)
	{
		*(res + i) = *(tmp + i);
		if (*(res + i) == (unsigned char)c)
			return (res + i + 1);
		i++;
	}
	return (NULL);
}
