/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hit2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:54:56 by jwoo              #+#    #+#             */
/*   Updated: 2021/04/23 18:55:34 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_quadratic	sphere_solution(t_ray cam_ray, t_sphere sphere)
{
	t_vector3	sphere_to_cam;
	t_quadratic	ret;

	sphere_to_cam = vec3_sub(cam_ray.origin, sphere.center);
	ret.a = vec3_dot(cam_ray.direct, cam_ray.direct);
	ret.half_b = vec3_dot(cam_ray.direct, sphere_to_cam);
	ret.c = vec3_dot(sphere_to_cam, sphere_to_cam) - sphere.r * sphere.r;
	ret.discriminant = ret.half_b * ret.half_b - ret.a * ret.c;
	return (ret);
}

t_inter				hit_sphere(t_ray cam_ray, t_sphere sphere, int idx)
{
	t_inter		inter;
	double		near;
	double		far;
	t_quadratic	sp_sol;

	inter_init(&inter, 's', idx);
	sp_sol = sphere_solution(cam_ray, sphere);
	near = (-sp_sol.half_b - sqrt(sp_sol.discriminant)) / (sp_sol.a);
	far = (-sp_sol.half_b + sqrt(sp_sol.discriminant)) / (sp_sol.a);
	if (far <= EPSILON)
		inter.solution = -1;
	else if (near <= EPSILON)
	{
		inter.inout = 1;
		inter.solution = far;
	}
	else
		inter.solution = near;
	return (inter);
}

t_inter				hit_plane(t_ray cam_ray, t_plane plane, int idx)
{
	t_inter		inter;
	double		pn_dot_cd;
	double		pn_dot_cp;

	inter_init(&inter, 'p', idx);
	pn_dot_cd = vec3_dot(plane.normal, cam_ray.direct);
	pn_dot_cp = vec3_dot(plane.normal, vec3_sub(plane.center, cam_ray.origin));
	if (pn_dot_cd != 0)
	{
		inter.solution = pn_dot_cp / pn_dot_cd;
		if (inter.solution <= EPSILON)
			inter.solution = -1;
	}
	return (inter);
}

t_inter				hit_square(t_ray cam_ray, t_square sq, int idx)
{
	t_inter		inter;
	double		sqn_dot_cd;
	double		sqn_dot_csq;
	t_vector3	hit;

	inter_init(&inter, 'q', idx);
	sqn_dot_cd = vec3_dot(sq.normal, cam_ray.direct);
	sqn_dot_csq = vec3_dot(sq.normal, vec3_sub(sq.center, cam_ray.origin));
	if (sqn_dot_cd != 0)
	{
		inter.solution = sqn_dot_csq / sqn_dot_cd;
		if (inter.solution <= EPSILON)
			inter.solution = -1;
		else
		{
			hit = vec3_sub(ray_hit_point(cam_ray, inter.solution), sq.center);
			if (!(pow(vec3_dot(hit, sq.vertical), 2) < pow((sq.size * 0.5), 2)
			&& pow(vec3_dot(hit, sq.horizontal), 2) < pow((sq.size * 0.5), 2)))
				inter.solution = -1;
		}
	}
	return (inter);
}
