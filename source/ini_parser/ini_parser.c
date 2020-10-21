/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:52:42 by epainter          #+#    #+#             */
/*   Updated: 2020/10/21 15:21:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static void			block_parse(char *txt, t_block *block)
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

static	t_block		*block_alloc(char *name)
{
	t_block			*block;

	if (!(block = (t_block*)malloc(sizeof(t_block))))
		parse_error(MALLOC_ERROR);
	block->next = NULL;
	block->pairs = NULL;
	if (!(block->name = name))
		parse_error(MALLOC_ERROR);
	return (block);
}

char				*find_block(char *txt, char **tmp)
{
	char			*block_txt;

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

void				find_blocks(t_block **blocks, char *txt)
{
	char			*block_txt;
	char			*tmp;
	t_block			*tmp_list;

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

int					ini_parser(char *file_name, t_block **res)
{
	char			*txt;

	read_file(file_name, &txt);
	find_blocks(res, txt);
	free(txt);
	return (SUCCESS);
}
