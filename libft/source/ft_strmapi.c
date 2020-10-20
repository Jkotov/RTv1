/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:03:52 by kroselin          #+#    #+#             */
/*   Updated: 2019/09/16 16:11:27 by kroselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	i = ft_strlen((char *)s);
	str = ft_memalloc(i + 1);
	if (!str)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f((unsigned int)i, (char)s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
