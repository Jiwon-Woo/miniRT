/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:53:40 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:33 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		atof_sign(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static int		atof_int(char **str)
{
	int	num;

	num = 0;
	while (**str != 0 && **str != '.')
	{
		if ('0' <= **str && **str <= '9')
			num = num * 10 + (**str - '0');
		else
			break ;
		(*str)++;
	}
	return (num);
}

static double	atof_point(char **str)
{
	double	num;
	int		i;

	i = -1;
	num = 0.0;
	while (**str != 0)
	{
		if ('0' <= **str && **str <= '9')
			num += (**str - '0') * pow(10, i--);
		else
			break ;
		(*str)++;
	}
	return (num);
}

double			rt_atof(char **str)
{
	int		integer;
	int		sign;
	double	point;
	double	ret;

	sign = atof_sign(str);
	integer = atof_int(str);
	point = 0.0;
	if (**str == '.')
	{
		(*str)++;
		point = atof_point(str);
	}
	ret = (integer + point) * sign;
	return (ret);
}
