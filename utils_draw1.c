/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:12 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:30 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	ray_color(t_ray cam_ray, t_inter inter, t_info *info)
{
	t_point_ray	*point_ray;
	t_inter		*shade;
	t_hit_light	*hit_info;
	t_all_light	all;
	t_vector3	last_light;

	if (inter.object != 'n' && inter.solution > 0)
	{
		point_ray = ret_point_light(cam_ray, inter, info);
		shade = ret_point_shade(point_ray, info);
		hit_info = get_object_light(point_ray, inter, info);
		all = light_sum(point_ray, shade, hit_info, info);
		last_light = vec3_multi(vec3_max_1(vec3_add(all.ambient, all.diffuse)),
								all.object_rgb);
		last_light = vec3_max_1(vec3_add(last_light, all.specular));
		return (last_light);
	}
	return (vec3_set(0, 0, 0));
}

int			color_vec3_to_int(t_data *data, t_vector3 pixel_color)
{
	int	r;
	int	g;
	int	b;

	r = ceil(255 * pixel_color.x);
	g = ceil(255 * pixel_color.y);
	b = ceil(255 * pixel_color.z);
	data->pixel_color = vec3_set(r * 256 * 256, g * 256, b);
	return (data->pixel_color.x + data->pixel_color.y + data->pixel_color.z);
}

int			get_pixel_color(t_info *info, t_camera *cam, double u, double v)
{
	t_ray		cam_ray;
	t_inter		inter;
	t_vector3	pixel_color;
	int			color;

	cam_ray = cam_to_screen_ray(*cam, u, v);
	inter = near_object(hit_object(cam_ray, info));
	pixel_color = ray_color(cam_ray, inter, info);
	color = color_vec3_to_int(info->data, pixel_color);
	return (color);
}
