/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:53:46 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:33 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rt_atoi(char *str, int *move)
{
	int	index;
	int	num;
	int	sign;

	sign = 1;
	index = 0;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	num = 0;
	while (str[index])
	{
		if ('0' <= str[index] && str[index] <= '9')
			num = num * 10 + (str[index] - '0');
		else
			break ;
		index++;
	}
	*move = index;
	return (sign * num);
}
