/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hit1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:53 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			inter_init(t_inter *inter, char object, int idx)
{
	inter->object = object;
	inter->inout = 0;
	inter->index = idx;
	inter->solution = -1;
}

t_inter			near_object(t_object_inter *object_inter)
{
	t_inter	ret;
	int		index;
	double	temp;

	ret = object_inter->nothing;
	index = -1;
	while (++index < object_inter->object_num)
	{
		temp = object_inter->object[index].solution;
		if (temp > EPSILON)
		{
			if (ret.object == 'n')
				ret = object_inter->object[index];
			else if (temp < ret.solution)
				ret = object_inter->object[index];
		}
	}
	free(object_inter->object);
	object_inter->object = 0;
	free(object_inter);
	object_inter = 0;
	return (ret);
}

void			object_inter_init(t_object_inter *obj_inter, t_info *info)
{
	obj_inter->sp_num = info->sp_num;
	obj_inter->pl_num = info->pl_num;
	obj_inter->sq_num = info->sq_num;
	obj_inter->tr_num = info->tr_num;
	obj_inter->cy_num = info->cy_num;
	obj_inter->object_num = obj_inter->sp_num + obj_inter->pl_num +
			obj_inter->sq_num + obj_inter->tr_num + obj_inter->cy_num;
	obj_inter->nothing.object = 'n';
	obj_inter->nothing.index = -1;
	obj_inter->nothing.inout = -1;
	obj_inter->nothing.solution = -1;
}

void			set_object_inter(t_object_inter *obj_inter, t_ray cam_ray,
									t_info *info)
{
	int	index;
	int	i;

	i = 0;
	index = -1;
	while (++index < obj_inter->sp_num)
		obj_inter->object[i++] = hit_sphere(cam_ray, info->sp[index], index);
	index = -1;
	while (++index < obj_inter->pl_num)
		obj_inter->object[i++] = hit_plane(cam_ray, info->pl[index], index);
	index = -1;
	while (++index < obj_inter->sq_num)
		obj_inter->object[i++] = hit_square(cam_ray, info->sq[index], index);
	index = -1;
	while (++index < obj_inter->cy_num)
		obj_inter->object[i++] = hit_cylinder(cam_ray, info->cy[index], index);
	index = -1;
	while (++index < obj_inter->tr_num)
		obj_inter->object[i++] = hit_triangle(cam_ray, info->tr[index], index);
}

t_object_inter	*hit_object(t_ray cam_ray, t_info *info)
{
	t_object_inter	*obj_inter;

	obj_inter = (t_object_inter *)malloc(sizeof(t_object_inter));
	if (obj_inter == 0)
		exit(1);
	object_inter_init(obj_inter, info);
	obj_inter->object =
			(t_inter *)malloc(sizeof(t_inter) * obj_inter->object_num);
	if (obj_inter->object == 0)
		exit(1);
	set_object_inter(obj_inter, cam_ray, info);
	return (obj_inter);
}
