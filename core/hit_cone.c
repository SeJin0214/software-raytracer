/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:52:03 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 20:18:38 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit_cone.h"
#include "equation.h"
#include "hit_cylinder.h"
#include "ft_math.h"

extern inline bool		is_hit_down_cap_in_cone(const t_ray ray, \
const t_cone *cone, const t_vector3 down_c, t_hit_record *out);

extern inline t_vector3	get_normal_in_cone(const t_vector3 point, \
const t_cone cone);

bool	is_hit_cone(const t_ray ray, \
const void *obj, t_hit_record *out)
{
	const t_cone				*co = obj;
	const t_quadratic_equation	quadratic = load_hit_cone_equation(ray, *co);
	float						solution;
	bool						is_hit;
	float						h;

	is_hit = is_hit_down_cap_in_cone(ray, co, co->shape.coordinates, out);
	solution = get_quadtatic_root_minus(quadratic);
	if (solution <= 0 || out->t <= solution)
	{
		solution = get_quadtatic_root_plus(quadratic);
		if (solution <= 0 || out->t <= solution)
			return (is_hit);
	}
	h = calculate_hit_height(ray, \
	co->shape.local_basis.row[Z], co->shape.coordinates, solution);
	if (quadratic.discriminant <= 0 || h > co->height || h <= __FLT_EPSILON__)
		return (is_hit);
	out->t = solution;
	out->point = get_point_in_ray(ray, solution);
	out->normal = get_normal_at_hit_point(co, \
	get_normal_in_cone(out->point, *co), out->point);
	out->color = get_color_at_hit_point(co, out->point);
	out->object = (void *)co;
	return (true);
}
