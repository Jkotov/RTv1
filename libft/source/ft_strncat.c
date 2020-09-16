/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:25:55 by kroselin          #+#    #+#             */
/*   Updated: 2020/09/16 15:27:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*dst;
	int		i;
	size_t	l;

	i = 0;
	l = 0;
	dst = s1;
	while (s1[l] != '\0')
	{
		dst[i] = s1[l];
		i++;
		l++;
	}
	l = 0;
	while (l < n && s2[l] != '\0')
	{
		dst[i] = s2[l];
		l++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
