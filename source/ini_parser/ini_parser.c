/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:52:42 by epainter          #+#    #+#             */
/*   Updated: 2020/10/20 18:56:44 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"
/*
** res should be NULL
** res should be free by freeing function after using
*/

char					*find_value(char *key, t_block *block)
{
	t_string_pair *tmp;

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

static t_string_pair	*pair_create(char *key, char *value)
{
	t_string_pair	*pair;

	if (!(pair = (t_string_pair *)malloc(sizeof(t_string_pair))))
		parse_error(MALLOC_ERROR);
	pair->key = key;
	pair->value = value;
	pair->next = NULL;
	return (pair);
}

static void				add_pair_to_block(t_block *block, t_string_pair *pair)
{
	t_string_pair *tmp;

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

static char				*skip_spaces(char *txt)
{
	if (!txt)
		return (NULL);
	while (ft_strchr(" \n\t\v\f\r", *txt) && *txt)
		txt++;
	return (txt);
}

static void				block_parse(char *txt, t_block *block)
{
	char			*tmp;
	char			*key;
	char			*value;

	txt = skip_spaces(txt);
	while (txt)
	{
		if (!*txt)
			return ;
		if (!(tmp = ft_strchr(txt, '=')))
			return ;
		if (!(key = ft_strsub(txt, 0, tmp - txt)))
			parse_error(MALLOC_ERROR);
		if (!(value = ft_strchr(tmp, '\n')))
			value = ft_strchr(tmp, '\0');
		if (!(value = ft_strsub(tmp, 1, value - tmp - 1)))
			if (ft_strchr(tmp, '\n') == NULL)
				value = ft_strdup("");
		if (value == NULL)
			parse_error(MALLOC_ERROR);
		add_pair_to_block(block, pair_create(key, value));
		txt++;
		txt = ft_strchr(txt, '\n');
		txt = skip_spaces(txt);
	}
}

static	t_block			*block_alloc(char *name)
{
	t_block	*block;

	if (!(block = (t_block*)malloc(sizeof(t_block))))
		parse_error(MALLOC_ERROR);
	block->next = NULL;
	block->pairs = NULL;
	if (!(block->name = name))
		parse_error(MALLOC_ERROR);
	return (block);
}

char					*find_block(char *txt, char **tmp)
{
	char	*block_txt;

	if (!(*tmp = ft_strchr(txt, ']')))
		parse_error(FILE_ERROR);
	if (!(block_txt = ft_strchr(txt + 1, '[')))
		block_txt = ft_strchr(txt + 1, '\0');
	if (*tmp > block_txt)
		parse_error(FILE_ERROR);
	if (!((block_txt = ft_strsub(*tmp, 1, block_txt - *tmp - 1))))
		parse_error(MALLOC_ERROR);
	return (block_txt);
}

void					find_blocks(t_block **blocks, char *txt)
{
	char	*block_txt;
	char	*tmp;
	t_block	*tmp_list;

	*blocks = block_alloc(ft_strdup("NULL"));
	if (!((block_txt = ft_strsub(txt, 0, ft_strchr(txt, '[') - txt))))
		parse_error(MALLOC_ERROR);
	block_parse(block_txt, (*blocks));
	free(block_txt);
	tmp_list = *blocks;
	txt = ft_strchr(txt, '[');
	while (txt)
	{
		block_txt = find_block(txt, &tmp);
		tmp_list->next = block_alloc(ft_strsub(txt, 1, tmp - txt - 1));
		tmp_list = tmp_list->next;
		block_parse(block_txt, tmp_list);
		free(block_txt);
		txt = ft_strchr(txt + 1, '[');
	}
}

static int				read_file(char *file_name, char **txt)
{
	int		fd;
	char	*buf;

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

int						ini_parser(char *file_name, t_block **res)
{
	char	*txt;

	read_file(file_name, &txt);
	find_blocks(res, txt);
	free(txt);
	return (SUCCESS);
}
