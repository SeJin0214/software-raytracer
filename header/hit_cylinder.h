/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:26:19 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:37:48 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_CYLINDER_BONUS_H
# define HIT_CYLINDER_BONUS_H
# include "solid_shape_getter.h"
# include "cylinder.h"

bool		is_hit_cylinder(const t_ray ray, \
const void* obj, t_hit_record* out);

/** 
 * P = O + tD
 * c = C + hB 
 * D = camera direction
 * N = local_basis[Z]
 * (P - c) * N = 0
 * (O + tD - c) * N = 0
 * NO + tND - Nc = 0
 * t = N(c - O) / ND 
*/	
inline bool	is_hit_up_cap(const t_ray ray, const t_cylinder* cylinder, \
const t_vector3 up_c, t_hit_record* out)
{
	const float		numerator = dot_product3x3(cylinder->\
	shape.local_basis.row[Z], subtract_vector3(up_c, ray.origin));
	const float		denominator = dot_product3x3(\
	cylinder->shape.local_basis.row[Z], ray.direction);
	float			solution;
	t_vector3		p;
	t_vector3		p_sub_c;

	if (denominator == 0 || numerator / denominator < 0 \
	|| numerator / denominator >= out->t)
		return (false);
	solution = numerator / denominator;
	p = get_point_in_ray(ray, solution);
	p_sub_c = subtract_vector3(p, up_c);
	if (get_length_in_vector3(p_sub_c) * get_length_in_vector3(p_sub_c) > \
	(cylinder->diameter / 2) * (cylinder->diameter / 2))
		return (false);
	out->t = solution;
	out->point = p;
	out->normal = get_normal_at_hit_point(\
	cylinder, cylinder->shape.local_basis.row[Z], out->point);
	out->color = get_color_at_hit_point(cylinder, out->point);
	out->object = (void *)cylinder;
	return (true);
}

inline bool	is_hit_down_cap(const t_ray ray, const t_cylinder* cylinder, \
const t_vector3 down_c, t_hit_record* out)
{
	const float		numerator = dot_product3x3(cylinder->\
	shape.local_basis.row[Z], subtract_vector3(down_c, ray.origin));
	const float		denominator = dot_product3x3(\
	cylinder->shape.local_basis.row[Z], ray.direction);
	float			solution;
	t_vector3		p;
	t_vector3		p_sub_c;

	if (denominator == 0 || numerator / denominator < 0 \
	|| numerator / denominator >= out->t)
		return (false);
	solution = numerator / denominator;
	p = get_point_in_ray(ray, solution);
	p_sub_c = subtract_vector3(p, down_c);
	if (dot_product3x3(p_sub_c, p_sub_c) > \
	(cylinder->diameter / 2) * (cylinder->diameter / 2))
		return (false);
	out->t = solution;
	out->point = p;
	out->normal = get_normal_at_hit_point(cylinder, multiply_vector3(\
	cylinder->shape.local_basis.row[Z], -1), out->point);
	out->color = get_color_at_hit_point(cylinder, out->point);
	out->object = (void *)cylinder;
	return (true);
}

inline bool	is_hit_cylinder_end_cap(const t_ray ray, \
const t_cylinder* cylinder, t_hit_record* out)
{
	const t_vector3	n = cylinder->shape.local_basis.row[Z];
	const t_ray		upward_ray = get_ray(cylinder->shape.coordinates, n);
	const t_vector3	up_c = get_point_in_ray(upward_ray, cylinder->height / 2);
	const t_vector3	down_c = get_point_in_ray(upward_ray, \
	-(cylinder->height / 2));
	bool			is_hit;

	is_hit = is_hit_up_cap(ray, cylinder, up_c, out);
	is_hit = is_hit_down_cap(ray, cylinder, down_c, out) || is_hit;
	return (is_hit);
}

inline float	calculate_hit_height(const t_ray ray, \
const t_vector3 n, const t_vector3 c, float t)
{
	const t_vector3	p = get_point_in_ray(ray, t);

	return (dot_product3x3(n, subtract_vector3(p, c)));
}

inline void	set_hit_record_in_cylinder(const t_ray ray, \
const t_cylinder *cy, const float solution, t_hit_record* out)
{
	const float	height = calculate_hit_height(ray, \
	cy->shape.local_basis.row[Z], cy->shape.coordinates, solution);
	t_ray		height_ray;
	t_vector3	radius;
	t_vector3	normal;

	out->t = solution;
	out->point = get_point_in_ray(ray, out->t);
	out->color = get_color_at_hit_point(cy, out->point);
	height_ray = get_ray(cy->shape.coordinates, cy->shape.local_basis.row[Z]);
	radius = subtract_vector3(out->point, get_point_in_ray(height_ray, height));
	normal = normalize_vector3(radius);
	out->normal = get_normal_at_hit_point(cy, normal, out->point);
	out->object = (void *)cy;
}

#endif