/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:20 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		set_sphere(t_info *info, t_rt *rt)
{
	int			index;
	t_sphere	*temp;
	t_list		*first;

	index = -1;
	first = rt->sp;
	while (++index < info->sp_num)
	{
		temp = rt->sp->content;
		info->sp[index] = *temp;
		rt->sp = rt->sp->next;
	}
	rt->sp = first;
}

void		set_plane(t_info *info, t_rt *rt)
{
	int		index;
	t_plane	*temp;
	t_list	*first;

	index = -1;
	first = rt->pl;
	while (++index < info->pl_num)
	{
		temp = rt->pl->content;
		info->pl[index] = *temp;
		rt->pl = rt->pl->next;
	}
	rt->pl = first;
}

void		set_square(t_info *info, t_rt *rt)
{
	int			index;
	t_square	*temp;
	t_list		*first;

	index = -1;
	first = rt->sq;
	while (++index < info->sq_num)
	{
		temp = rt->sq->content;
		info->sq[index] = *temp;
		rt->sq = rt->sq->next;
	}
	rt->sq = first;
}

void		set_triangle(t_info *info, t_rt *rt)
{
	int			index;
	t_triangle	*temp;
	t_list		*first;

	index = -1;
	first = rt->tr;
	while (++index < info->tr_num)
	{
		temp = rt->tr->content;
		info->tr[index] = *temp;
		rt->tr = rt->tr->next;
	}
	rt->tr = first;
}

void		set_cylinder(t_info *info, t_rt *rt)
{
	int			index;
	t_cylinder	*temp;
	t_list		*first;

	index = -1;
	first = rt->cy;
	while (++index < info->cy_num)
	{
		temp = rt->cy->content;
		info->cy[index] = *temp;
		rt->cy = rt->cy->next;
	}
	rt->cy = first;
}
