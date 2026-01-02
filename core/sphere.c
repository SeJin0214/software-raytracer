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
#include "vtable.h"

static const t_vtable sphere_table = 
{ 
	.is_hit = is_hit_sphere, 
	.get_uv_coordinate = get_uv_coordinate_in_sphere,
	.delete = delete_sphere, 
	.scale_height = update_scale_height_sphere,
	.scale_diameter = update_scale_diameter_sphere, 
};

extern inline void		set_hit_record_by_sphere(t_hit_record* out, \
const float solution, const t_ray ray, const t_sphere* sphere);

void	init_sphere(t_sphere* out_sphere, const t_vector3 coordinates, \
	const t_ivector3 colors, const t_image texture, const float diameter)
{
	t_shape shape;
	init_shape(&shape, coordinates, colors, get_local_basis((t_vector3){{0.0f, 0.0f, 1.0f}}), texture, &sphere_table);
	out_sphere->shape = shape;
	out_sphere->diameter = diameter;
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
	const t_vector3			oc = subtract_vector3(ray.origin, sphere->shape.coordinates);
	t_quadratic_equation	equation;

	equation.a = dot_product3x3(ray.direction, ray.direction);
	equation.b = 2.0f * dot_product3x3(oc, ray.direction);
	equation.c = dot_product3x3(oc, oc) - (sphere->diameter / 2) * (sphere->diameter / 2);
	equation.discriminant = equation.b * equation.b - 4 * equation.a * equation.c;
	if (equation.discriminant <= 0)
	{
		return (false);
	}
	float solution = get_quadtatic_root_minus(equation);
	if (solution <= 0 || out->t < solution)
	{
		solution = get_quadtatic_root_plus(equation);
		if (solution <= 0 || out->t < solution)
		{
			return (false);
		}
	}
	set_hit_record_by_sphere(out, solution, ray, sphere);
	return (true);
}
