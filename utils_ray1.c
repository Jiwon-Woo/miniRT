/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:13 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray		ray_create(t_vector3 origin, t_vector3 direct)
{
	t_ray	ret;

	ret.origin = origin;
	ret.direct = vec3_unit(direct);
	return (ret);
}

t_vector3	ray_hit_point(t_ray ray, double t)
{
	t_vector3	ret;

	ret = vec3_add(ray.origin, vec3_scalar(ray.direct, t));
	return (ret);
}

t_ray		cam_to_screen_ray(t_camera cam, double u, double v)
{
	t_ray		cam_ray;
	t_vector3	one_pixel;
	t_vector3	temp;

	cam_ray.origin = cam.origin;
	temp = vec3_add(vec3_scalar(cam.horizontal, u),
		vec3_scalar(cam.vertical, v));
	one_pixel = vec3_add(cam.lower_left_corner, temp);
	cam_ray.direct = vec3_unit(vec3_sub(one_pixel, cam_ray.origin));
	return (cam_ray);
}
