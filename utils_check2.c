/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:53:56 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:33 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		check_r(char **factor, t_rt *rt)
{
	int	move;

	if (!(factor[1] != 0 && factor[2] != 0 && factor[3] == 0))
		return (-1);
	if (rt->r.screen_x > 0 || rt->r.screen_y > 0)
		return (-1);
	rt->r.screen_x = rt_atoi(factor[1], &move);
	if (*(factor[1] + move) != 0 || rt->r.screen_x <= 0)
		return (-1);
	rt->r.screen_y = rt_atoi(factor[2], &move);
	if (*(factor[2] + move) != 0 || rt->r.screen_y <= 0)
		return (-1);
	return (1);
}

int		check_a(char **factor, t_rt *rt)
{
	char	**comma;

	if (!(factor[1] != 0 && factor[2] != 0 && factor[3] == 0))
		return (-1);
	if (rt->a.ratio > 0)
		return (-1);
	if (check_set_num(&(rt->a.ratio), factor[1]) == -1)
		return (-1);
	if (!(rt->a.ratio > 0.0 && rt->a.ratio <= 1.0))
		return (-1);
	comma = split_comma(factor[2]);
	if (check_set_vec3(&(rt->a.color), comma) == -1)
		return (-1);
	rt->a.color = vec3_scalar(rt->a.color, 1.0 / 255.0);
	if (check_vec3_in_range(rt->a.color, 0.0, 1.0) == -1)
		return (-1);
	if (vec3_len(rt->a.color) == 0)
		return (-1);
	return (1);
}

int		check_c(char **factor, t_rt *rt)
{
	t_cam_info	*c;
	char		**comma;

	c = (t_cam_info *)malloc(sizeof(t_cam_info));
	if (c == 0)
		exit(1);
	if (!(factor[1] != 0 && factor[2] != 0 && factor[3] != 0 && factor[4] == 0))
		return (-1);
	comma = split_comma(factor[1]);
	if (check_set_vec3(&(c->origin), comma) == -1)
		return (-1);
	comma = split_comma(factor[2]);
	if (check_set_vec3(&(c->direct), comma) == -1)
		return (-1);
	if (vec3_len(c->direct) == 0.0)
		return (-1);
	c->direct = vec3_unit(c->direct);
	if (check_set_num(&(c->fov), factor[3]) == -1)
		return (-1);
	if (!(c->fov > 0.0 && c->fov <= 180.0))
		return (-1);
	ft_lstadd_front(&(rt->c), ft_lstnew(c));
	return (1);
}

int		check_l(char **factor, t_rt *rt)
{
	t_light	*l;
	char	**comma;

	l = (t_light *)malloc(sizeof(t_light));
	if (l == 0)
		exit(1);
	if (!(factor[1] != 0 && factor[2] != 0 && factor[3] != 0 && factor[4] == 0))
		return (-1);
	comma = split_comma(factor[1]);
	if (check_set_vec3(&(l->origin), comma) == -1)
		return (-1);
	if (check_set_num(&(l->brightness), factor[2]) == -1)
		return (-1);
	if (!(l->brightness >= 0.0 && l->brightness <= 1.0))
		return (-1);
	comma = split_comma(factor[3]);
	if (check_set_vec3(&(l->color), comma) == -1)
		return (-1);
	l->color = vec3_scalar(l->color, 1.0 / 255.0);
	if (check_vec3_in_range(l->color, 0.0, 1.0) == -1)
		return (-1);
	ft_lstadd_front(&(rt->l), ft_lstnew(l));
	return (1);
}
