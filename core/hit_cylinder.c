/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:46:14 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:55:10 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "equation.h"
#include "hit_cylinder.h"
#include "solid_shape_getter.h"

bool	is_hit_cylinder(const t_ray ray, \
const void *obj, t_hit_record *out)
{
	const t_cylinder			*cy = obj;
	const t_quadratic_equation	quadratic = load_hit_cy_equation(ray, *cy);
	float						solution;
	bool						is_hit;
	float						height;

	is_hit = is_hit_cylinder_end_cap(ray, cy, out);
	solution = get_quadtatic_root_minus(quadratic);
	if (solution <= 0 || out->t <= solution)
	{
		solution = get_quadtatic_root_plus(quadratic);
		if (solution <= 0 || out->t <= solution)
			return (is_hit);
	}
	height = calculate_hit_height(ray, cy->shape.local_basis.row[Z], \
	cy->shape.coordinates, solution);
	if (quadratic.discriminant <= 0 || fabsf(height) > cy->height / 2)
		return (is_hit);
	set_hit_record_in_cylinder(ray, cy, solution, out);
	return (true);
}

extern inline float	calculate_hit_height(const t_ray ray, \
const t_vector3 n, const t_vector3 c, float t);

extern inline void	set_hit_record_in_cylinder(const t_ray ray, \
const t_cylinder *cy, const float solution, t_hit_record *out);

extern inline bool	is_hit_cylinder_end_cap(const t_ray ray, \
const t_cylinder *cylinder, t_hit_record *out);

extern inline bool	is_hit_up_cap(const t_ray ray, \
const t_cylinder *cylinder, const t_vector3 up_c, t_hit_record *out);

extern inline bool	is_hit_down_cap(const t_ray ray, \
const t_cylinder *cylinder, const t_vector3 down_c, t_hit_record *out);
