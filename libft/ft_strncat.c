/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:58:00 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *append, size_t n)
{
	size_t len_dst;
	size_t len_app;

	len_dst = ft_strlen(dst);
	len_app = ft_strlen(append);
	if (len_app < n)
		ft_strncpy(&*(dst + len_dst), append, len_app);
	else
		ft_strncpy(&*(dst + len_dst), append, n);
	if (n > len_app)
		*(dst + len_app + len_dst) = '\0';
	else
		*(dst + n + len_dst) = '\0';
	return (dst);
}
