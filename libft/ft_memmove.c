/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:43:14 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*res;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (dst);
	i = 0;
	tmp = (unsigned char*)src;
	res = (unsigned char*)dst;
	if (src < dst)
	{
		while (n--)
			*(res + n) = *(tmp + n);
	}
	else
	{
		while (i < n)
		{
			*(res + i) = *(tmp + i);
			i++;
		}
	}
	return (res);
}
