/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bmp1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:53:49 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:33 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		init_bmp_header(t_bmp *bmp, t_info *info)
{
	bmp->file_type1 = 'B';
	bmp->file_type2 = 'M';
	bmp->file_size = 4 * info->r.screen_x * info->r.screen_y + 54;
	bmp->reserved1 = 0;
	bmp->reserved2 = 0;
	bmp->pixel_data_offset = 54;
	bmp->header_size = 40;
	bmp->image_width = info->r.screen_x;
	bmp->image_height = -info->r.screen_y;
	bmp->planes = 1;
	bmp->bit_per_pixel = 32;
	bmp->compression = 0;
	bmp->image_size = 4 * info->r.screen_x * info->r.screen_y;
	bmp->x_pixel_per_meter = info->r.screen_x;
	bmp->y_pixel_per_meter = info->r.screen_y;
	bmp->total_color = 0x00ffffff;
	bmp->important_color = 0;
}

void		save_bmp(int bmp_fd, t_info *info)
{
	t_bmp	bmp_header;
	int		padding;
	int		i;
	int		j;

	init_bmp_header(&bmp_header, info);
	padding = (info->data->line_length / 4);
	write(bmp_fd, &bmp_header, 54);
	i = -1;
	while (++i < info->r.screen_y)
	{
		j = -1;
		while (++j < info->r.screen_x)
			write(bmp_fd, &info->data->addr[(i * padding + j) * 4], 4);
	}
	close(bmp_fd);
}

int			check_save_ret_fd(int argc, char **argv)
{
	int fd;

	fd = -42;
	if (argc == 3 && ft_strncmp(argv[2], "--save\0", 7) == 0)
	{
		if ((fd = open("jwoo.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0644)) < 0)
		{
			printf("Fail to create bmp file.\nERROR!\n");
			return (-1);
		}
	}
	return (fd);
}
