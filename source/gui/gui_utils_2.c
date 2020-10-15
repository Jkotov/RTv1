#include "../../include/rtv1.h"

void 			del_objs(t_surface **list)
{
	while ((*list)->next)
		list = &(*list)->next;
	free(*list);
	*list = NULL;
}

int 			count_objs(t_surface *list)
{
	int 		i;

	i = 0;
	while (list->next)
	{
		list = list->next;
		i++;
	}
	return(i);
}
