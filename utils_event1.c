/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_event1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:17 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 19:08:09 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			key_check(int key, t_info *info)
{
	t_camera	*cam;

	if (key == ESC)
	{
		mlx_destroy_window(info->data->ptr, info->data->window);
		exit(0);
	}
	if (key == CHANGECAMERA)
	{
		info->c = info->c->next;
		cam = info->c->content;
		draw_pixel(info, cam);
		mlx_put_image_to_window(info->data->ptr, info->data->window,
								info->data->image, 0, 0);
	}
	return (0);
}

int			button_check(t_info *info)
{
	mlx_destroy_window(info->data->ptr, info->data->window);
	exit(0);
	return (0);
}
