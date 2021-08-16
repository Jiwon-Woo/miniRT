/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:08 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:33 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_cy_vec(t_cylinder *cy, char **factor)
{
	char		**comma;

	comma = split_comma(factor[1]);
	if (check_set_vec3(&(cy->center), comma) == -1)
		return (-1);
	comma = split_comma(factor[2]);
	if (check_set_vec3(&(cy->normal), comma) == -1)
		return (-1);
	if (vec3_len(cy->normal) == 0.0)
		return (-1);
	cy->normal = vec3_unit(cy->normal);
	comma = split_comma(factor[3]);
	if (check_set_vec3(&(cy->color), comma) == -1)
		return (-1);
	cy->color = vec3_scalar(cy->color, 1.0 / 255.0);
	if (check_vec3_in_range(cy->color, 0.0, 1.0) == -1)
		return (-1);
	return (1);
}

int			check_cy(char **factor, t_rt *rt)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cy == 0)
		exit(1);
	if (!(factor[1] != 0 && factor[2] != 0 && factor[3] != 0 &&
		factor[4] != 0 && factor[5] != 0 && factor[6] == 0))
		return (-1);
	if (check_cy_vec(cy, factor) == -1)
		return (-1);
	if (check_set_num(&(cy->r), factor[4]) == -1)
		return (-1);
	if (check_set_num(&(cy->h), factor[5]) == -1)
		return (-1);
	if (cy->r <= 0.0 || cy->h <= 0.0)
		return (-1);
	ft_lstadd_front(&(rt->cy), ft_lstnew(cy));
	return (1);
}

static int	check_tr_man(char **factor, t_triangle *tr)
{
	char	**comma;

	comma = split_comma(factor[1]);
	if (check_set_vec3(&(tr->p1), comma) == -1)
		return (-1);
	comma = split_comma(factor[2]);
	if (check_set_vec3(&(tr->p2), comma) == -1)
		return (-1);
	comma = split_comma(factor[3]);
	if (check_set_vec3(&(tr->p3), comma) == -1)
		return (-1);
	comma = split_comma(factor[4]);
	if (check_set_vec3(&(tr->color), comma) == -1)
		return (-1);
	tr->color = vec3_scalar(tr->color, 1.0 / 255.0);
	if (check_vec3_in_range(tr->color, 0.0, 1.0) == -1)
		return (-1);
	return (1);
}

static int	check_tr_bonus(t_triangle *tr)
{
	t_vector3	p1p2;
	t_vector3	p2p3;

	p1p2 = vec3_sub(tr->p2, tr->p1);
	p2p3 = vec3_sub(tr->p3, tr->p2);
	tr->normal = vec3_cross(p1p2, p2p3);
	if (vec3_len(tr->normal) == 0.0)
		return (-1);
	tr->normal = vec3_unit(tr->normal);
	return (1);
}

int			check_tr(char **factor, t_rt *rt)
{
	t_triangle	*tr;

	tr = (t_triangle *)malloc(sizeof(t_triangle));
	if (tr == 0)
		exit(1);
	if (!(factor[1] != 0 && factor[2] != 0 && factor[3] != 0
		&& factor[4] != 0 && factor[5] == 0))
		return (-1);
	if (check_tr_man(factor, tr) == -1)
		return (-1);
	if (check_tr_bonus(tr) == -1)
		return (-1);
	ft_lstadd_front(&(rt->tr), ft_lstnew(tr));
	return (1);
}
