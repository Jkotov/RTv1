/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 17:54:02 by kroselin          #+#    #+#             */
/*   Updated: 2020/09/16 15:27:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	count_start(char const *s)
{
	int		j;

	j = 0;
	while (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')
		j++;
	return (j);
}

static int	count_end(char const *s)
{
	int		i;
	size_t	len;

	len = ft_strlen(s);
	i = len - 1;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i--;
	return (i);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		j;
	int		i;
	int		c;

	if (!s)
		return (0);
	j = count_start(s);
	i = count_end(s);
	c = 0;
	if (i < j)
	{
		str = ft_strnew(0);
		return (str);
	}
	if (!(str = ft_memalloc((i - j) + 2)))
		return (0);
	while (j <= i)
	{
		str[c] = s[j];
		c++;
		j++;
	}
	return (str);
}
