/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:59:06 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 20:16:16 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "sphere.h"
#include "equation.h"
#include "render.h"

extern inline void		set_hit_record_by_sphere(t_hit_record* out, \
const float solution, const t_ray ray, const t_sphere* sphere);

t_sphere*	init_construction_to_sphere(const t_sphere sphere, t_world* world)
{
	t_sphere*	result;

	result = malloc(sizeof(t_sphere));
	result->shape = sphere.shape;
	result->shape.local_basis = \
	get_local_basis((t_vector3){{0.0f, 0.0f, 1.0f}});
	result->shape.texture_type = TEXTURE_BASIC;
	result->shape.texture = world->texture;
	result->shape.checkerboard_scale = 10;
	result->shape.is_hit = is_hit_sphere;
	result->shape.delete = delete_sphere;
	result->shape.get_uv_coordinate = get_uv_coordinate_in_sphere;
	result->shape.scale_diameter = update_scale_diameter_sphere;
	result->shape.scale_height = update_scale_height_sphere;
	result->diameter = sphere.diameter;
	return (result);
}

void	delete_sphere(void* obj)
{
	free(obj);
}

t_vector2	get_uv_coordinate_in_sphere(const void* sphere, const t_vector3 hit_point)
{
	t_vector2		uv;
	t_vector3		local;
	const t_sphere	*sp = sphere;
	const t_vector3	n = normalize_vector3(\
	subtract_vector3(hit_point, sp->shape.coordinates));

	local.x = dot_product3x3(n, sp->shape.local_basis.row[X]);
	local.y = dot_product3x3(n, sp->shape.local_basis.row[Y]);
	local.z = dot_product3x3(n, sp->shape.local_basis.row[Z]);
	uv.x = (atan2f(local.z, local.x) + PI) / (2 * PI);
	uv.y = acosf(local.y) / PI;
	return (uv);
}

bool	is_hit_sphere(const t_ray ray, const void* obj, t_hit_record* out)
{
	const t_sphere*			sphere = obj;
	const t_vector3			oc = \
	subtract_vector3(ray.origin, sphere->shape.coordinates);
	t_quadratic_equation	equation;
	float					solution;

	equation.a = dot_product3x3(ray.direction, ray.direction);
	equation.b = 2.0f * dot_product3x3(oc, ray.direction);
	equation.c = dot_product3x3(oc, oc) - (sphere->diameter / 2) \
	* (sphere->diameter / 2);
	equation.discriminant = equation.b * equation.b \
	- 4 * equation.a * equation.c;
	if (equation.discriminant <= 0)
		return (false);
	solution = get_quadtatic_root_minus(equation);
	if (solution <= 0 || out->t < solution)
	{
		solution = get_quadtatic_root_plus(equation);
		if (solution <= 0 || out->t < solution)
			return (false);
	}
	set_hit_record_by_sphere(out, solution, ray, sphere);
	return (true);
}
