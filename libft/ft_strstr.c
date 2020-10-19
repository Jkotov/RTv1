/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:47:58 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	size_t i;

	i = 0;
	if (*str2 == '\0')
		return ((char*)str1);
	while (*str1)
	{
		while (*(str1 + i) == *(str2 + i))
		{
			i++;
			if (*(str2 + i) == '\0')
				return ((char*)str1);
		}
		i = 0;
		str1++;
	}
	return (NULL);
}
