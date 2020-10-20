/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kroselin <kroselin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:48:33 by kroselin          #+#    #+#             */
/*   Updated: 2019/09/16 17:05:11 by kroselin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memalloc(size_t size)
{
	void *memory;

	memory = (void *)malloc(sizeof(*memory) * size);
	if (!memory)
		return (NULL);
	ft_bzero(memory, size);
	return (memory);
}
