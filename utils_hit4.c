/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hit4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:55:00 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_quadratic	cylinder_solution(t_ray cam_ray, t_cylinder cylinder)
{
	t_quadratic	ret;
	t_vector3	cc_co;
	t_vector3	cn;
	double		cd_dot_cn;
	double		cc_co_dot_cn;

	cc_co = vec3_sub(cam_ray.origin, cylinder.center);
	cn = vec3_add(cylinder.center, cylinder.normal);
	cd_dot_cn = vec3_dot(cam_ray.direct, cylinder.normal);
	cc_co_dot_cn = vec3_dot(cc_co, cylinder.normal);
	ret.a = vec3_dot(cam_ray.direct, cam_ray.direct) - cd_dot_cn * cd_dot_cn;
	ret.half_b = vec3_dot(cam_ray.direct, cc_co) - cd_dot_cn * cc_co_dot_cn;
	ret.c = vec3_dot(cc_co, cc_co) - pow(cc_co_dot_cn, 2) - pow(cylinder.r, 2);
	ret.discriminant = ret.half_b * ret.half_b - ret.a * ret.c;
	return (ret);
}

static void			is_cylinder_in(t_inter *inter, t_cylinder cy, t_ray cam_ray,
								double far)
{
	t_vector3	hit;
	double		cp_dot_n;

	inter->solution = far;
	inter->inout = 1;
	hit = ray_hit_point(cam_ray, inter->solution);
	cp_dot_n = vec3_dot(vec3_sub(hit, cy.center), cy.normal);
	if (cp_dot_n * cp_dot_n > (cy.h / 2.0) * (cy.h / 2.0))
		inter->solution = -1;
}

t_inter				hit_cylinder(t_ray cam_ray, t_cylinder cylinder, int idx)
{
	t_inter		inter;
	t_quadratic	cy_sol;
	double		cp_dot_n;
	double		near;
	double		far;

	inter_init(&inter, 'c', idx);
	cy_sol = cylinder_solution(cam_ray, cylinder);
	near = (-cy_sol.half_b - sqrt(cy_sol.discriminant)) / (cy_sol.a);
	far = (-cy_sol.half_b + sqrt(cy_sol.discriminant)) / (cy_sol.a);
	if (far <= EPSILON)
		inter.solution = -1;
	else if (near <= EPSILON)
		is_cylinder_in(&inter, cylinder, cam_ray, far);
	else
	{
		inter.solution = near;
		cp_dot_n = vec3_dot(vec3_sub(ray_hit_point(cam_ray, inter.solution),
										cylinder.center), cylinder.normal);
		if (cp_dot_n * cp_dot_n > (cylinder.h / 2.0) * (cylinder.h / 2.0))
			is_cylinder_in(&inter, cylinder, cam_ray, far);
	}
	return (inter);
}
