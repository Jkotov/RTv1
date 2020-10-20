/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 19:12:01 by epainter          #+#    #+#             */
/*   Updated: 2020/10/20 16:42:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

void	parse_error(int code)
{
	if (code == MALLOC_ERROR)
		ft_putstr("Memory allocation error\n");
	if (code == FILE_ERROR)
		ft_putstr("File error\n");
	exit(code);
}
