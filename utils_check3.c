/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:03 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:54:33 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			check_sp(char **factor, t_rt *rt)
{
	t_sphere	*sp;
	char		**comma;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (sp == 0)
		exit(1);
	if (!(factor[1] != 0 && factor[2] != 0 && factor[3] != 0 && factor[4] == 0))
		return (-1);
	comma = split_comma(factor[1]);
	if (check_set_vec3(&(sp->center), comma) == -1)
		return (-1);
	if (check_set_num(&(sp->r), factor[2]) == -1)
		return (-1);
	if (sp->r <= 0.0)
		return (-1);
	comma = split_comma(factor[3]);
	if (check_set_vec3(&(sp->color), comma) == -1)
		return (-1);
	sp->color = vec3_scalar(sp->color, 1.0 / 255.0);
	if (check_vec3_in_range(sp->color, 0.0, 1.0) == -1)
		return (-1);
	ft_lstadd_front(&(rt->sp), ft_lstnew(sp));
	return (1);
}

int			check_pl(char **factor, t_rt *rt)
{
	t_plane	*pl;
	char	**comma;

	pl = (t_plane *)malloc(sizeof(t_plane));
	if (pl == 0)
		exit(1);
	if (!(factor[1] != 0 && factor[2] != 0 && factor[3] != 0 && factor[4] == 0))
		return (-1);
	comma = split_comma(factor[1]);
	if (check_set_vec3(&(pl->center), comma) == -1)
		return (-1);
	comma = split_comma(factor[2]);
	if (check_set_vec3(&(pl->normal), comma) == -1)
		return (-1);
	if (vec3_len(pl->normal) == 0.0)
		return (-1);
	pl->normal = vec3_unit(pl->normal);
	comma = split_comma(factor[3]);
	if (check_set_vec3(&(pl->color), comma) == -1)
		return (-1);
	pl->color = vec3_scalar(pl->color, 1.0 / 255.0);
	if (check_vec3_in_range(pl->color, 0.0, 1.0) == -1)
		return (-1);
	ft_lstadd_front(&(rt->pl), ft_lstnew(pl));
	return (1);
}

static int	check_sq_man(char **factor, t_square *sq)
{
	char	**comma;

	comma = split_comma(factor[1]);
	if (check_set_vec3(&(sq->center), comma) == -1)
		return (-1);
	comma = split_comma(factor[2]);
	if (check_set_vec3(&(sq->normal), comma) == -1)
		return (-1);
	if (vec3_len(sq->normal) == 0.0)
		return (-1);
	sq->normal = vec3_unit(sq->normal);
	if (check_set_num(&(sq->size), factor[3]) == -1)
		return (-1);
	if (sq->size <= 0.0)
		return (-1);
	comma = split_comma(factor[4]);
	if (check_set_vec3(&(sq->color), comma) == -1)
		return (-1);
	sq->color = vec3_scalar(sq->color, 1.0 / 255.0);
	if (check_vec3_in_range(sq->color, 0.0, 1.0) == -1)
		return (-1);
	return (1);
}

static void	check_sq_bonus(t_square *sq)
{
	t_vector3	temp;

	temp = vec3_cross(vec3_set(0, 1, 0), sq->normal);
	if (vec3_len(temp) != 0)
	{
		sq->horizontal = vec3_unit(temp);
		sq->vertical = vec3_unit(vec3_cross(sq->normal, sq->horizontal));
	}
	else
	{
		temp = vec3_cross(sq->normal, vec3_set(1, 0, 0));
		sq->vertical = vec3_unit(temp);
		sq->horizontal = vec3_unit(vec3_cross(sq->vertical, sq->normal));
	}
}

int			check_sq(char **factor, t_rt *rt)
{
	t_square	*sq;

	sq = (t_square *)malloc(sizeof(t_square));
	if (sq == 0)
		exit(1);
	if (!(factor[1] != 0 && factor[2] != 0 && factor[3] != 0
			&& factor[4] != 0 && factor[5] == 0))
		return (-1);
	if (check_sq_man(factor, sq) == -1)
		return (-1);
	check_sq_bonus(sq);
	ft_lstadd_front(&(rt->sq), ft_lstnew(sq));
	return (1);
}
