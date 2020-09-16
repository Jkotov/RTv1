/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:19:09 by kroselin          #+#    #+#             */
/*   Updated: 2020/09/16 15:27:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memdup(void const *src, size_t len)
{
	void	*dst;
	size_t	i;

	i = 0;
	if ((dst = malloc(len)) == NULL)
		return (NULL);
	while (i < len)
	{
		((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	return (dst);
}
