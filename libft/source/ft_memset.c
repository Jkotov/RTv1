/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:29:33 by kroselin          #+#    #+#             */
/*   Updated: 2019/09/13 10:04:09 by kroselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *src, int c, size_t len)
{
	unsigned char	*ptr;
	int				i;

	i = 0;
	ptr = src;
	while (i < (int)len)
	{
		*ptr = (unsigned char)c;
		ptr++;
		i++;
	}
	return (src);
}
