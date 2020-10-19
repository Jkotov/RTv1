/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:36:17 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	res;
	int				flag;

	res = 0;
	flag = 1;
	while (ft_strchr(" \n\t\v\f\r", *str) && *str)
		str++;
	if (*str == '-' && (*(str + 1) > '9' || *(str + 1) < '0'))
		return (0);
	if (*str == '-')
		flag = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = 10 * res + (*str - '0');
		if ((res > 9223372036854775807 && flag == 1))
			return (-1);
		if (res > (unsigned long)(9223372036854775807 - flag) && flag == -1)
			return (0);
		str++;
	}
	return ((int)res * flag);
}
