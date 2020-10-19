/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdirect <mdirect@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:49:06 by mdirect           #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count_words(char *s, char c)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (*s)
	{
		if (*s == c && i == 1)
			i = 0;
		if (*s != c && i == 0)
		{
			i = 1;
			res++;
		}
		s++;
	}
	return (res);
}

static int	ft_count_wordlen(char *s, char c)
{
	int res;

	res = 0;
	while (*s && *s != c)
	{
		res++;
		s++;
	}
	return (res);
}

static void	ft_free(char **w, size_t n)
{
	while (n--)
		ft_strdel(&w[n]);
	free(*w);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**word;
	size_t	w;
	size_t	i;

	if (!s)
		return (NULL);
	w = ft_count_words((char *)s, c);
	if (!(word = (char **)malloc(sizeof(*word) * (w + 1))))
		return (NULL);
	i = 0;
	while (i < w)
	{
		while (*s == c && *s)
			s++;
		if (!(word[i] = ft_strsub((char *)s, 0,
				ft_count_wordlen((char *)s, c))))
		{
			ft_free(word, i);
			return (NULL);
		}
		s = s + ft_count_wordlen((char *)s, c);
		i++;
	}
	word[i] = NULL;
	return (word);
}
