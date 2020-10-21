/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_ini_blocks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 10:50:53 by epainter          #+#    #+#             */
/*   Updated: 2020/10/20 18:41:29 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"


void	clean_pairs(t_string_pair *pair)
{
	if (!pair)
		return ;
	if (pair->next)
		clean_pairs(pair->next);
	free(pair->key);
	free(pair->value);
	free(pair);
}

void	clean_blocks(t_block *block)
{
	if (!block)
		return ;
	if (block->next)
		clean_blocks(block->next);
	clean_pairs(block->pairs);
	free(block->name);
	free(block);
}

void	cleanup_ini(t_block *ini)
{
	clean_blocks(ini);
}
