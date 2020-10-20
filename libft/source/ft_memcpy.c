/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 09:54:20 by kroselin          #+#    #+#             */
/*   Updated: 2019/09/16 18:36:32 by kroselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void *i;

	i = dst;
	if (!dst && !src)
		return (0);
	while (n--)
	{
		*((unsigned char *)dst) = *((const unsigned char *)src);
		dst++;
		src++;
	}
	return (i);
}
