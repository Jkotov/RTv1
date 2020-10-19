/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:59:10 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (*str2 == '\0')
		return ((char*)str1);
	if (len == 0)
		return (NULL);
	while (*(str1 + j))
	{
		while (*(str1 + i + j) == *(str2 + i))
		{
			if (i + j >= len)
				return (NULL);
			i++;
			if (*(str2 + i) == '\0')
				return ((char*)(str1 + j));
		}
		i = 0;
		j++;
	}
	return (NULL);
}
