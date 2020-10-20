/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epainter <epainter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 23:56:21 by epainter          #+#    #+#             */
/*   Updated: 2020/10/19 05:34:48 by epainter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_atoi_base(const char *str, int str_base)
{
	unsigned	int	res;
	char			digits[17];
	int				flag;

	ft_strcpy(digits, "0123456789abcdef");
	digits[str_base] = '\0';
	res = 0;
	flag = 1;
	while (ft_strchr(" \n\t\v\f\r", *str) && *str)
		str++;
	if (*str == '-' && !ft_strchr(digits, ft_tolower(*(str + 1))))
		return (0);
	if (*str == '-')
		flag = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_strchr(digits, ft_tolower(*str)) && *str)
	{
		res = str_base * res + (ft_strchr(digits, ft_tolower(*str)) - digits);
		str++;
	}
	return ((int)res * flag);
}
