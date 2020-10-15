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

t_surface 		*last_shape(t_surface **list)
{
	t_surface	*head;

	if(!(head = (t_surface*)malloc(sizeof(t_surface))))
		sdl_error("Alloc error");
	head = (*list);
	while ((*list)->next != NULL)
	{
		printf("list color = %d\n", (*list)->color);
		list = &(*list)->next;
	}

	return (*list);
}