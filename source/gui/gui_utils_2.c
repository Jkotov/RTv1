#include "../../include/rtv1.h"


t_surface 		*select_last(t_surface **list, int nb)
{
//	t_surface *head;
//
//	head = (*list);
	while ((*list)->number != nb && (*list)->next != NULL)
		list = &(*list)->next;
//	if((*list)->next == NULL && nb == (*list)->number + 1)
//		(*list) = head;
	printf ("nb = %i\n", nb);
	return (*list);
}

void 	give_number(t_surface **list)
{
	int 	i;

	i = 0;
	while ((*list)->next) {
		(*list)->number = i;
		list = &(*list)->next;
		i++;
	}
	(*list)->number = i;
}


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
