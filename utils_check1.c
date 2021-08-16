/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:53:53 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:33 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_comma(char **comma)
{
	free(comma[0]);
	free(comma[1]);
	free(comma[2]);
	comma[0] = 0;
	comma[1] = 0;
	comma[2] = 0;
	free(comma);
	comma = 0;
}

void	set_start_pointer(char **p1, char **p2)
{
	p1[0] = p2[0];
	p1[1] = p2[1];
	p1[2] = p2[2];
}

int		check_set_vec3(t_vector3 *vec, char **comma)
{
	char	*start[3];

	if (comma == 0 ||
		!(comma[0] != 0 && comma[1] != 0 && comma[2] != 0 && comma[3] == 0))
		return (-1);
	set_start_pointer(start, comma);
	if (ft_strlen(comma[0]) == 1 && (*(comma[0]) == '-' || *(comma[0]) == '+'))
		return (-1);
	if (ft_strlen(comma[1]) == 1 && (*(comma[1]) == '-' || *(comma[1]) == '+'))
		return (-1);
	if (ft_strlen(comma[2]) == 1 && (*(comma[2]) == '-' || *(comma[2]) == '+'))
		return (-1);
	*vec = vec3_set(rt_atof(&comma[0]), rt_atof(&comma[1]), rt_atof(&comma[2]));
	if (*(comma[0]) != 0 || *(comma[1]) != 0 || *(comma[2]) != 0)
		return (-1);
	set_start_pointer(comma, start);
	free_comma(comma);
	return (1);
}

int		check_vec3_in_range(t_vector3 vec, double min, double max)
{
	if (!(vec.x >= min && vec.x <= max))
		return (-1);
	if (!(vec.y >= min && vec.y <= max))
		return (-1);
	if (!(vec.z >= min && vec.z <= max))
		return (-1);
	return (1);
}

int		check_set_num(double *num, char *factor)
{
	char	*start;

	if (factor == 0)
		return (-1);
	if (ft_strlen(factor) == 1 && (*factor == '-' || *factor == '+'))
		return (-1);
	start = factor;
	*num = rt_atof(&factor);
	if (*(factor) != 0)
		return (-1);
	factor = start;
	return (1);
}
