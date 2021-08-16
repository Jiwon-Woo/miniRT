/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:16 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		set_ra_count_object_num(t_info *info, t_rt *rt)
{
	info->a = rt->a;
	info->r = rt->r;
	info->c_num = ft_lstsize(rt->c);
	info->l_num = ft_lstsize(rt->l);
	info->sp_num = ft_lstsize(rt->sp);
	info->pl_num = ft_lstsize(rt->pl);
	info->sq_num = ft_lstsize(rt->sq);
	info->tr_num = ft_lstsize(rt->tr);
	info->cy_num = ft_lstsize(rt->cy);
}

void		set_light(t_info *info, t_rt *rt)
{
	int		index;
	t_light *temp;
	t_list	*first;

	index = -1;
	first = rt->l;
	while (++index < info->l_num)
	{
		temp = rt->l->content;
		info->l[index] = *temp;
		rt->l = rt->l->next;
	}
	rt->l = first;
}

static void	camera_coordi_init(t_camera *cam)
{
	t_vector3	temp;

	temp = vec3_cross(vec3_set(0, 1, 0), cam->direct);
	if (vec3_len(temp) != 0)
	{
		cam->horizontal = vec3_unit(temp);
		cam->vertical = vec3_unit(vec3_cross(cam->direct, cam->horizontal));
	}
	else
	{
		temp = vec3_cross(cam->direct, vec3_set(1, 0, 0));
		cam->vertical = vec3_unit(temp);
		cam->horizontal = vec3_unit(vec3_cross(cam->vertical, cam->direct));
	}
	cam->horizontal = vec3_scalar(cam->horizontal, cam->viewport_w);
	cam->vertical = vec3_scalar(cam->vertical, cam->viewport_h);
	cam->lower_left_corner = vec3_add(cam->viewport_center,
								vec3_add(vec3_scalar(cam->horizontal, -0.5),
								vec3_scalar(cam->vertical, -0.5)));
}

t_camera	*camera_create(t_cam_info *c, t_resoltion r)
{
	t_camera	*cam;
	t_ray		cam_ray;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (cam == 0)
		exit(1);
	cam->origin = c->origin;
	cam->direct = c->direct;
	cam->fov = c->fov;
	cam->screen_ratio = (double)r.screen_x / (double)r.screen_y;
	cam->focal_length = 1.0;
	cam->viewport_w = 2.0 * cam->focal_length * tan(cam->fov * 0.5 * PI / 180);
	cam->viewport_h = cam->viewport_w / cam->screen_ratio;
	cam_ray = ray_create(cam->origin, cam->direct);
	cam->viewport_center = ray_hit_point(cam_ray, cam->focal_length);
	camera_coordi_init(cam);
	return (cam);
}

void		set_camera(t_info *info, t_rt *rt)
{
	int			i;
	t_list		*first;
	t_camera	*camera;
	t_cam_info	*cam_info;

	i = -1;
	first = rt->c;
	while (++i < info->c_num)
	{
		cam_info = rt->c->content;
		camera = camera_create(cam_info, rt->r);
		ft_lstadd_front(&(info->c), ft_lstnew(camera));
		rt->c = rt->c->next;
	}
	rt->c = first;
	ft_lstadd_back(&(info->c), info->c);
}
