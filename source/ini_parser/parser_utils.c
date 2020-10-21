/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:09:38 by root              #+#    #+#             */
/*   Updated: 2020/10/21 15:17:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

/*
** res should be NULL
** res should be free by freeing function after using
*/

char				*find_value(char *key, t_block *block)
{
	t_string_pair	*tmp;

	if (!block)
		return ("");
	tmp = block->pairs;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

t_string_pair		*pair_create(char *key, char *value)
{
	t_string_pair	*pair;

	if (!(pair = (t_string_pair *)malloc(sizeof(t_string_pair))))
		parse_error(MALLOC_ERROR);
	pair->key = key;
	pair->value = value;
	pair->next = NULL;
	return (pair);
}

void				add_pair_to_block(t_block *block, t_string_pair *pair)
{
	t_string_pair	*tmp;

	if (!block)
		parse_error(UNKNOWN_ERROR);
	tmp = block->pairs;
	if (!tmp)
	{
		block->pairs = pair;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = pair;
}

char				*skip_spaces(char *txt)
{
	if (!txt)
		return (NULL);
	while (ft_strchr(" \n\t\v\f\r", *txt) && *txt)
		txt++;
	return (txt);
}

int					read_file(char *file_name, char **txt)
{
	int				fd;
	char			*buf;

	if ((fd = open(file_name, O_RDONLY)) < 1)
		parse_error(FILE_ERROR);
	if (read(fd, NULL, 0) < 0)
		parse_error(FILE_ERROR);
	if (!(*txt = ft_strnew(0)))
		parse_error(MALLOC_ERROR);
	if (!(buf = ft_strnew(BUFF_SIZE)))
		parse_error(MALLOC_ERROR);
	while (read(fd, buf, BUFF_SIZE))
	{
		*txt = ft_strjoinfree(txt, &buf, 1);
		ft_bzero(buf, BUFF_SIZE);
	}
	close(fd);
	free(buf);
	return (SUCCESS);
}
