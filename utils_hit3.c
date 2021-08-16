/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hit3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:57 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_tr_sol	set_triangle_solution(t_triangle triangle)
{
	t_tr_sol	ret;

	ret.p1p2 = vec3_sub(triangle.p2, triangle.p1);
	ret.p1p3 = vec3_sub(triangle.p3, triangle.p1);
	ret.p2p3 = vec3_sub(triangle.p3, triangle.p2);
	ret.p2p1 = vec3_sub(triangle.p1, triangle.p2);
	ret.p3p1 = vec3_sub(triangle.p1, triangle.p3);
	ret.p3p2 = vec3_sub(triangle.p2, triangle.p3);
	return (ret);
}

static int		is_in_triangle(t_tr_sol sol, t_triangle tr, t_vector3 hit)
{
	t_vector3	hp[3];
	double		temp[3];

	hp[0] = vec3_sub(tr.p1, hit);
	hp[1] = vec3_sub(tr.p2, hit);
	hp[2] = vec3_sub(tr.p3, hit);
	temp[0] = vec3_dot(vec3_cross(sol.p2p1, sol.p3p1),
						vec3_cross(hp[0], sol.p3p1));
	temp[1] = vec3_dot(vec3_cross(sol.p3p2, sol.p1p2),
						vec3_cross(hp[1], sol.p1p2));
	temp[2] = vec3_dot(vec3_cross(sol.p1p3, sol.p2p3),
						vec3_cross(hp[2], sol.p2p3));
	if (temp[0] > 0 && temp[1] > 0 && temp[2] > 0)
		return (1);
	return (-1);
}

t_inter			hit_triangle(t_ray cam_ray, t_triangle tr, int idx)
{
	t_inter		inter;
	double		tn_dot_cd;
	double		tn_dot_cp;
	t_vector3	hit;
	t_tr_sol	sol;

	inter_init(&inter, 't', idx);
	tn_dot_cd = vec3_dot(tr.normal, cam_ray.direct);
	tn_dot_cp = vec3_dot(tr.normal, vec3_sub(tr.p1, cam_ray.origin));
	sol = set_triangle_solution(tr);
	if (tn_dot_cd != 0)
	{
		inter.solution = tn_dot_cp / tn_dot_cd;
		if (inter.solution <= EPSILON)
			inter.solution = -1;
		else
		{
			hit = ray_hit_point(cam_ray, inter.solution);
			if (is_in_triangle(sol, tr, hit) != 1)
				inter.solution = -1;
		}
	}
	return (inter);
}
