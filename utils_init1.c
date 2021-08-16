/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:03 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		info_init(t_info *info, t_rt *rt, t_data *data)
{
	set_ra_count_object_num(info, rt);
	info->data = data;
	info->c = NULL;
	info->l = (t_light *)malloc(sizeof(t_light) * info->l_num);
	info->sp = (t_sphere *)malloc(sizeof(t_sphere) * info->sp_num);
	info->pl = (t_plane *)malloc(sizeof(t_plane) * info->pl_num);
	info->sq = (t_square *)malloc(sizeof(t_square) * info->sq_num);
	info->tr = (t_triangle *)malloc(sizeof(t_triangle) * info->tr_num);
	info->cy = (t_cylinder *)malloc(sizeof(t_cylinder) * info->cy_num);
	if (info->l == 0 || info->sp == 0 || info->pl == 0 ||
		info->sq == 0 || info->tr == 0 || info->cy == 0)
		exit(1);
	set_light(info, rt);
	set_sphere(info, rt);
	set_plane(info, rt);
	set_square(info, rt);
	set_triangle(info, rt);
	set_cylinder(info, rt);
	set_camera(info, rt);
}

void		rt_init(t_rt *rt)
{
	rt->r.screen_x = 0.0;
	rt->r.screen_y = 0.0;
	rt->a.ratio = 0.0;
	rt->a.color = vec3_set(0.0, 0.0, 0.0);
	rt->c = NULL;
	rt->l = NULL;
	rt->sp = NULL;
	rt->pl = NULL;
	rt->sq = NULL;
	rt->tr = NULL;
	rt->cy = NULL;
}

t_resoltion	limit_screen(t_resoltion rt_r, t_resoltion max)
{
	t_resoltion	ret;

	if (rt_r.screen_x < max.screen_x)
		ret.screen_x = rt_r.screen_x;
	else
		ret.screen_x = max.screen_x;
	if (rt_r.screen_y < max.screen_y)
		ret.screen_y = rt_r.screen_y;
	else
		ret.screen_y = max.screen_y;
	return (ret);
}

void		data_init(t_data *data, t_rt *rt)
{
	data->ptr = mlx_init();
	if (data->ptr == 0)
		exit(1);
	mlx_get_screen_size(data->ptr, &(data->max.screen_x),
						&(data->max.screen_y));
	rt->r = limit_screen(rt->r, data->max);
	data->window = mlx_new_window(data->ptr, rt->r.screen_x, rt->r.screen_y,
								"miniRT");
	data->image = mlx_new_image(data->ptr, rt->r.screen_x, rt->r.screen_y);
	if (data->window == 0 || data->image == 0)
		exit(1);
	data->addr = mlx_get_data_addr(data->image, &(data->bits_per_pixel),
									&(data->line_length), &(data->endian));
	if (data->addr == 0)
		exit(1);
}
