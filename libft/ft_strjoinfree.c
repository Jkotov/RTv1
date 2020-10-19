/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:27:06 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** keys 0 - nofree 1 - free(s1); 2 - free(s2); 3 - free(s1 && s2)
*/

char	*ft_strjoinfree(char **s1, char **s2, int key)
{
	char	*res;

	if (s1 == NULL || s2 == NULL || key > 4 || key < 0)
		return (NULL);
	res = ft_strjoin(*s1, *s2);
	if ((key % 2) == 1)
	{
		free(*s1);
		*s1 = NULL;
		s1 = NULL;
	}
	if (key > 1)
	{
		free(*s2);
		*s2 = NULL;
		s2 = NULL;
	}
	return (res);
}
