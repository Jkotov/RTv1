/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 11:26:11 by kroselin          #+#    #+#             */
/*   Updated: 2020/09/16 15:27:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n--)
	{
		if (*((const unsigned char *)src) == (unsigned char)c)
		{
			*((unsigned char *)dst) = *((const unsigned char *)src);
			dst++;
			src++;
			return ((unsigned char *)dst);
		}
		*((unsigned char *)dst) = *((const unsigned char *)src);
		dst++;
		src++;
	}
	return (0);
}
