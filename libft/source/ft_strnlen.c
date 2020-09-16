/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:57:11 by kroselin          #+#    #+#             */
/*   Updated: 2020/09/16 15:27:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strnlen(const char *src, size_t maxlen)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (src[i] != '\0' && maxlen > 0)
	{
		i++;
		len++;
		maxlen--;
	}
	return (len);
}
