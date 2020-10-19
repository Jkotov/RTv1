/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 19:12:01 by epainter          #+#    #+#             */
/*   Updated: 2020/06/10 19:17:24 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ini_parser.h"
#include <stdlib.h>
#include "rtv1.h"

void	parse_error(int code)
{
	if (code == MALLOC_ERROR)
		ft_putstr("Memory allocation error\n");
	if (code == FILE_ERROR)
		ft_putstr("File error\n");
	exit(code);
}
