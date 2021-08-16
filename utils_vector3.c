/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vector3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:32 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	vec3_max_1(t_vector3 u)
{
	if (u.x >= 1.000000)
		u.x = 1.0;
	if (u.y >= 1.000000)
		u.y = 1.0;
	if (u.z >= 1.000000)
		u.z = 1.0;
	return (u);
}

t_vector3	vec3_set(double x, double y, double z)
{
	t_vector3	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vector3	rotate_x(t_vector3 vec, double theta)
{
	t_vector3	ret;

	ret.x = vec.x;
	ret.y = cos(theta) * vec.y - sin(theta) * vec.z;
	ret.z = sin(theta) * vec.y + cos(theta) * vec.z;
	return (ret);
}

t_vector3	rotate_y(t_vector3 vec, double theta)
{
	t_vector3	ret;

	ret.x = cos(theta) * vec.x - sin(theta) * vec.z;
	ret.y = vec.y;
	ret.z = sin(theta) * vec.x + cos(theta) * vec.z;
	return (ret);
}

t_vector3	rotate_z(t_vector3 vec, double theta)
{
	t_vector3	ret;

	ret.x = cos(theta) * vec.x - sin(theta) * vec.y;
	ret.y = sin(theta) * vec.x + cos(theta) * vec.y;
	ret.z = vec.z;
	return (ret);
}
