/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 12:30:45 by epainter          #+#    #+#             */
/*   Updated: 2020/10/21 11:31:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

void		sdl_error(char *text)
{
	ft_putstr(text);
	ft_putstr(SDL_GetError());
	exit(1);
}
