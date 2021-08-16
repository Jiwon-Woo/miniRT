/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vector1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:28 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	vec3_add(t_vector3 u, t_vector3 v)
{
	t_vector3	ret;

	ret.x = u.x + v.x;
	ret.y = u.y + v.y;
	ret.z = u.z + v.z;
	return (ret);
}

t_vector3	vec3_sub(t_vector3 u, t_vector3 v)
{
	t_vector3	ret;

	ret.x = u.x - v.x;
	ret.y = u.y - v.y;
	ret.z = u.z - v.z;
	return (ret);
}

t_vector3	vec3_multi(t_vector3 u, t_vector3 v)
{
	t_vector3	ret;

	ret.x = u.x * v.x;
	ret.y = u.y * v.y;
	ret.z = u.z * v.z;
	return (ret);
}

t_vector3	vec3_div(t_vector3 u, t_vector3 v)
{
	t_vector3	ret;

	ret.x = u.x / v.x;
	ret.y = u.y / v.y;
	ret.z = u.z / v.z;
	return (ret);
}
