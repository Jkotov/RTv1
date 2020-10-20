/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:36:04 by kroselin          #+#    #+#             */
/*   Updated: 2019/09/18 22:54:05 by kroselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if (!(size + 1))
		return (0);
	str = ft_memalloc(size + 1);
	if (!str)
		return (0);
	*str = '\0';
	return (str);
}
