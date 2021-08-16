/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vector2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:30 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	vec3_scalar(t_vector3 vec, double scalar)
{
	t_vector3	ret;

	ret.x = vec.x * scalar;
	ret.y = vec.y * scalar;
	ret.z = vec.z * scalar;
	return (ret);
}

double		vec3_dot(t_vector3 u, t_vector3 v)
{
	double	dot_product;

	dot_product = u.x * v.x + u.y * v.y + u.z * v.z;
	return (dot_product);
}

t_vector3	vec3_cross(t_vector3 u, t_vector3 v)
{
	t_vector3	ret;

	ret.x = u.y * v.z - u.z * v.y;
	ret.y = u.z * v.x - u.x * v.z;
	ret.z = u.x * v.y - u.y * v.x;
	return (ret);
}

double		vec3_len(t_vector3 vec)
{
	double	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (len);
}

t_vector3	vec3_unit(t_vector3 vec)
{
	t_vector3	ret;

	ret = vec3_scalar(vec, (1 / vec3_len(vec)));
	return (ret);
}
