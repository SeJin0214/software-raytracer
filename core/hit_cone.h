/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:42:57 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:56:38 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_CONE_BONUS_H
# define HIT_CONE_BONUS_H
# include "cone.h"
# include "hit_cone.h"
# include "solid_shape_getter2.h"

inline bool	is_hit_down_cap_in_cone(const t_ray ray, const t_cone *cone, \
const t_vector3 down_c, t_hit_record *out)
{
	const float		numerator = dot_product3x3(cone->\
	shape.local_basis.row[Z], subtract_vector3(down_c, ray.origin));
	const float		denominator = dot_product3x3(\
	cone->shape.local_basis.row[Z], ray.direction);
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
	(cone->diameter / 2) * (cone->diameter / 2))
		return (false);
	out->t = solution;
	out->point = p;
	out->normal = get_normal_at_hit_point(cone, multiply_vector3(\
	cone->shape.local_basis.row[Z], -1), out->point);
	out->color = get_color_at_hit_point(cone, out->point);
	out->object = (void *)cone;
	return (true);
}

inline t_vector3	get_normal_in_cone(const t_vector3 point, const t_cone cone)
{
	const t_vector3	vectex_to_c = \
	multiply_vector3(cone.shape.local_basis.row[Z], -1);
	const t_vector3	vertex_to_p = \
	normalize_vector3(subtract_vector3(point, \
	add_vector3(cone.shape.coordinates, \
	multiply_vector3(cone.shape.local_basis.row[Z], cone.height))));
	const t_vector3	proj_c = \
	multiply_vector3(vectex_to_c, dot_product3x3(vectex_to_c, vertex_to_p));
	const t_vector3	proj_p = \
	multiply_vector3(vertex_to_p, dot_product3x3(proj_c, vertex_to_p));
	const t_vector3	surface_normal = \
	normalize_vector3(subtract_vector3(proj_c, proj_p));

	return (surface_normal);
}

#endif
