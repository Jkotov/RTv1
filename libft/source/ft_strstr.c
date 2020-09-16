/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 10:08:51 by kroselin          #+#    #+#             */
/*   Updated: 2020/09/16 15:27:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	int i[4];

	i[0] = -1;
	i[1] = -1;
	i[2] = 0;
	if (str2[0] == '\0')
		return ((char *)str1);
	while (str1[++i[0]] != '\0')
	{
		while (str1[++i[1]] != '\0')
		{
			i[3] = i[1];
			while (str1[i[1]++] == str2[i[2]++])
			{
				if (str2[i[2]] == '\0')
					return ((char *)&str1[i[3]]);
			}
			i[1] = i[3];
			i[2] = 0;
		}
		i[1] = i[0];
	}
	return (0);
}
