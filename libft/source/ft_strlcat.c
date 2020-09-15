/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 12:10:19 by kroselin          #+#    #+#             */
/*   Updated: 2019/09/19 13:31:22 by kroselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*new_dst;
	size_t	i;
	size_t	l;
	size_t	count;
	size_t	rem;

	i = ft_strlen(dst);
	l = 0;
	if (!size)
		return (size + (ft_strlen(src)));
	new_dst = dst;
	rem = i;
	if (i >= size)
		return (size + (ft_strlen(src)));
	count = size - i - 1;
	while (l < count)
		new_dst[i++] = src[l++];
	new_dst[i] = '\0';
	if (rem > size)
		return (size + (ft_strlen(src)));
	else
		return (rem + (ft_strlen(src)));
}
