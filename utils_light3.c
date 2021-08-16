/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_light3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:10 by jwoo              #+#    #+#             */
/*   Updated: 2021/05/05 10:40:29 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_light_info(t_point_ray *pr, t_inter *shade, t_hit_light *hl)
{
	free(shade);
	shade = 0;
	free(pr->limit_len);
	pr->limit_len = 0;
	free(pr->point_to_light);
	pr->point_to_light = 0;
	free(pr);
	pr = 0;
	free(hl->diffuse);
	hl->diffuse = 0;
	free(hl->n_dot_pl);
	hl->n_dot_pl = 0;
	free(hl);
	hl = 0;
}

static void	all_light_init(t_all_light *all, t_hit_light *pl, t_info *info)
{
	all->object_rgb = pl->object_rgb;
	all->ambient = vec3_scalar(info->a.color, info->a.ratio);
	all->diffuse = vec3_set(0.0, 0.0, 0.0);
	all->specular = vec3_set(0.0, 0.0, 0.0);
}

t_all_light	light_sum(t_point_ray *pr, t_inter *shade, t_hit_light *pl,
						t_info *info)
{
	int			idx;
	t_all_light	all;
	t_vector3	reflect;
	double		r_dot_pco;
	double		n_len;

	idx = -1;
	all_light_init(&all, pl, info);
	while (++idx < info->l_num)
	{
		if (pl->diffuse[idx] > 0 && shade[idx].object == 'n')
		{
			all.diffuse = vec3_add(all.diffuse,
				vec3_scalar(info->l[idx].color, pl->diffuse[idx]));
			n_len = vec3_dot(pr->point_to_light[idx], pl->normal);
			reflect = vec3_unit(vec3_sub(vec3_scalar(pl->normal, n_len * 2),
										pr->point_to_light[idx]));
			r_dot_pco = vec3_dot(reflect, pr->point_to_cam);
			if (r_dot_pco > 0.0)
				all.specular = vec3_add(all.specular, vec3_scalar(
			info->l[idx].color, pow(r_dot_pco, 5) * info->l[idx].brightness));
		}
	}
	free_light_info(pr, shade, pl);
	return (all);
}
