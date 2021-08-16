/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_light2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:08 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point_ray	*ret_point_light(t_ray cam_ray, t_inter inter, t_info *info)
{
	t_point_ray	*pr;
	int			index;

	pr = (t_point_ray *)malloc(sizeof(t_point_ray));
	if (pr == 0)
		exit(1);
	pr->point = ray_hit_point(cam_ray, inter.solution);
	pr->point_to_cam = vec3_unit(vec3_sub(cam_ray.origin, pr->point));
	pr->point_to_light = (t_vector3 *)malloc(sizeof(t_vector3) * info->l_num);
	pr->limit_len = (double *)malloc(sizeof(double) * info->l_num);
	if (pr->point_to_light == 0 || pr->limit_len == 0)
		exit(1);
	index = -1;
	while (++index < info->l_num)
	{
		pr->point_to_light[index] = vec3_sub(info->l[index].origin, pr->point);
		pr->limit_len[index] = vec3_len(pr->point_to_light[index]);
		pr->point_to_light[index] = vec3_unit(pr->point_to_light[index]);
	}
	return (pr);
}

t_inter		*ret_point_shade(t_point_ray *point_ray, t_info *info)
{
	int				index;
	t_ray			ray;
	t_inter			*ret;
	t_object_inter	*temp;

	index = -1;
	ret = (t_inter *)malloc(sizeof(t_inter) * info->l_num);
	if (ret == 0)
		exit(1);
	while (++index < info->l_num)
	{
		ray = ray_create(point_ray->point, point_ray->point_to_light[index]);
		temp = hit_object(ray, info);
		ret[index] = near_object(temp);
		if (ret[index].solution - point_ray->limit_len[index] >= EPSILON)
			ret[index] = temp->nothing;
	}
	return (ret);
}

t_hit_light	*get_object_light(t_point_ray *pr, t_inter inter, t_info *info)
{
	t_hit_light *hit_light;

	hit_light = (t_hit_light *)malloc(sizeof(t_hit_light));
	if (hit_light == 0)
		exit(1);
	hit_light->n_dot_pl = (double *)malloc(sizeof(double) * info->l_num);
	hit_light->diffuse = (double *)malloc(sizeof(double) * info->l_num);
	if (hit_light->n_dot_pl == 0 || hit_light->diffuse == 0)
		exit(1);
	if (inter.object == 's')
		get_sphere_light(hit_light, pr, inter, info);
	else if (inter.object == 'p')
		get_plane_light(hit_light, pr, inter, info);
	else if (inter.object == 'q')
		get_square_light(hit_light, pr, inter, info);
	else if (inter.object == 't')
		get_triangle_light(hit_light, pr, inter, info);
	else if (inter.object == 'c')
		get_cylinder_light(hit_light, pr, inter, info);
	return (hit_light);
}
