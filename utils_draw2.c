/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:15 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 19:08:21 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr +
			(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void		draw_pixel(t_info *info, t_camera *cam)
{
	int			x;
	int			y;
	double		u;
	double		v;
	int			color;

	y = 0;
	while (y < info->r.screen_y)
	{
		x = 0;
		while (x < info->r.screen_x)
		{
			u = (info->r.screen_x - (double)x - 1) / (info->r.screen_x - 1);
			v = (info->r.screen_y - (double)y - 1) / (info->r.screen_y - 1);
			color = get_pixel_color(info, cam, u, v);
			my_mlx_pixel_put(info->data, x, y, color);
			++x;
		}
		++y;
	}
}

void		draw_window_loop(t_info *info, int bmp_fd)
{
	t_camera	*cam;

	cam = info->c->content;
	draw_pixel(info, cam);
	if (bmp_fd >= 0)
	{
		save_bmp(bmp_fd, info);
		exit(0);
	}
	mlx_put_image_to_window(info->data->ptr, info->data->window,
							info->data->image, 0, 0);
	mlx_hook(info->data->window, KEYPRESS, 1L << 0, key_check, info);
	mlx_hook(info->data->window, DESTROYNOTIFY, 1L << 17, button_check, info);
	mlx_loop(info->data->ptr);
}
