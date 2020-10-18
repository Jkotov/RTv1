/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:52:59 by root              #+#    #+#             */
/*   Updated: 2020/10/18 20:31:02 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

void			del_light(t_light **list)
{
	while ((*list)->next)
		list = &(*list)->next;
	free(*list);
	*list = NULL;
}

int				count_light(t_light *list)
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
