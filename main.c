/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:53 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:55 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	minirt(int argc, char **argv)
{
	int		fd;
	int		bmp_fd;
	t_rt	*rt;
	t_data	*data;
	t_info	*info;

	rt = (t_rt *)malloc(sizeof(t_rt));
	if (rt == 0)
		exit(1);
	rt_init(rt);
	fd = check_arg_ret_fd(argc, argv);
	if (fd < 0 || (fd >= 0 && check_rt_file(fd, rt) == -1))
		exit(1);
	data = (t_data *)malloc(sizeof(t_data));
	if (data == 0)
		exit(1);
	data_init(data, rt);
	info = (t_info *)malloc(sizeof(t_info));
	if (info == 0)
		exit(1);
	info_init(info, rt, data);
	bmp_fd = check_save_ret_fd(argc, argv);
	if (bmp_fd == -1)
		exit(1);
	draw_window_loop(info, bmp_fd);
}

int		main(int argc, char *argv[])
{
	minirt(argc, argv);
	return (0);
}
