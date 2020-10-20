/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 20:41:28 by epainter          #+#    #+#             */
/*   Updated: 2020/10/18 20:46:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_surface		*select_last(t_surface **list, int nb)
{
//	t_surface *head;
//
//	head = (*list);
	while ((*list)->number != nb && (*list)->next != NULL)
		list = &(*list)->next;
//	if((*list)->next == NULL && nb == (*list)->number + 1)
//		(*list) = head;
	printf("nb = %i\n", nb); // Не забудь удалить
	return (*list);
}

void			give_number(t_surface **list)
{
	int	i;

	i = 0;
	while ((*list)->next)
	{
		(*list)->number = i;
		list = &(*list)->next;
		i++;
	}
	(*list)->number = i;
}

void			del_objs(t_surface **list)
{
	while ((*list)->next)
		list = &(*list)->next;
	free(*list);
	*list = NULL;
}

int				count_objs(t_surface *list)
{
	int	i;

	i = 0;
	while (list->next)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void			init_menu(t_sdl *sdl)
{
	sdl->menu.menu_size = (SDL_Rect){0, 0, sdl->width, 300};
	sdl->menu.img = create_texture("menu.png", sdl);
}
