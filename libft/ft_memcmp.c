/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:37:46 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (*((unsigned char*)str1 + i) ==\
	*((unsigned char*)str2 + i) && i < n - 1)
		i++;
	return (*((unsigned char*)str1 + i) - *((unsigned char*)str2 + i));
}
