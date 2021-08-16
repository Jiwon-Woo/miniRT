/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_light1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:05 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		*get_sphere_light(t_hit_light *hl, t_point_ray *pr, t_inter inter,
								t_info *info)
{
	int	idx;

	hl->normal = vec3_unit(vec3_sub(pr->point,
									info->sp[inter.index].center));
	hl->object_rgb = info->sp[inter.index].color;
	if (inter.inout == 1)
		hl->normal = vec3_scalar(hl->normal, -1);
	idx = -1;
	while (++idx < info->l_num)
	{
		hl->n_dot_pl[idx] = vec3_dot(pr->point_to_light[idx], hl->normal);
		hl->diffuse[idx] = info->l[idx].brightness * hl->n_dot_pl[idx];
	}
	return (hl);
}

void		*get_plane_light(t_hit_light *hl, t_point_ray *pr, t_inter inter,
								t_info *info)
{
	int	idx;

	hl->normal = vec3_unit(info->pl[inter.index].normal);
	hl->object_rgb = info->pl[inter.index].color;
	if (vec3_dot(hl->normal, pr->point_to_cam) < 0)
		hl->normal = vec3_scalar(hl->normal, -1);
	idx = -1;
	while (++idx < info->l_num)
	{
		hl->n_dot_pl[idx] = vec3_dot(pr->point_to_light[idx],
										hl->normal);
		hl->diffuse[idx] = info->l[idx].brightness * hl->n_dot_pl[idx];
	}
	return (hl);
}

void		*get_square_light(t_hit_light *hl, t_point_ray *pr, t_inter inter,
								t_info *info)
{
	int	idx;

	hl->normal = vec3_unit(info->sq[inter.index].normal);
	hl->object_rgb = info->sq[inter.index].color;
	if (vec3_dot(hl->normal, pr->point_to_cam) < 0)
		hl->normal = vec3_scalar(hl->normal, -1);
	idx = -1;
	while (++idx < info->l_num)
	{
		hl->n_dot_pl[idx] = vec3_dot(pr->point_to_light[idx], hl->normal);
		hl->diffuse[idx] = info->l[idx].brightness * hl->n_dot_pl[idx];
	}
	return (hl);
}

void		*get_cylinder_light(t_hit_light *hl, t_point_ray *pr, t_inter inter,
								t_info *info)
{
	t_vector3	ccp;
	t_vector3	h;
	t_vector3	cl;
	int			idx;

	hl->object_rgb = info->cy[inter.index].color;
	ccp = vec3_sub(pr->point, info->cy[inter.index].center);
	h = vec3_scalar(info->cy[inter.index].normal,
					vec3_dot(ccp, info->cy[inter.index].normal));
	hl->normal = vec3_unit(vec3_sub(ccp, h));
	if (inter.inout == 1)
		hl->normal = vec3_scalar(hl->normal, -1);
	idx = -1;
	while (++idx < info->l_num)
	{
		cl = vec3_unit(vec3_sub(info->l[idx].origin,
						info->cy[inter.index].center));
		hl->n_dot_pl[idx] = vec3_dot(cl, hl->normal);
		hl->diffuse[idx] = info->l[idx].brightness * hl->n_dot_pl[idx];
	}
	return (hl);
}

void		*get_triangle_light(t_hit_light *hl, t_point_ray *pr, t_inter inter,
								t_info *info)
{
	int	idx;

	hl->normal = vec3_unit(info->tr[inter.index].normal);
	hl->object_rgb = info->tr[inter.index].color;
	if (vec3_dot(hl->normal, pr->point_to_cam) < 0)
		hl->normal = vec3_scalar(hl->normal, -1);
	idx = -1;
	while (++idx < info->l_num)
	{
		hl->n_dot_pl[idx] = vec3_dot(pr->point_to_light[idx], hl->normal);
		hl->diffuse[idx] = info->l[idx].brightness * hl->n_dot_pl[idx];
	}
	return (hl);
}
