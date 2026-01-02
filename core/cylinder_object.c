/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_object.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:31:39 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 02:44:53 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "cylinder.h"
#include "hit_cylinder.h"
#include "equation.h"
#include "solid_shape_getter.h"

static t_vtable cylinder_table = 
{ 
	.is_hit = is_hit_cylinder, 
	.get_uv_coordinate = get_uv_coordinate_in_cylinder,
	.delete = delete_cylinder, 
	.scale_height = update_scale_height_cylinder,
	.scale_diameter = update_scale_diameter_cylinder, 
};

void	init_cylinder(t_cylinder* out_cylinder, const t_vector3 coordinates, \
	const t_ivector3 colors, const t_vector3 direction, const t_image texture, const float diameter, const float height)
{
	t_shape shape;
	init_shape(&shape, coordinates, colors, get_local_basis(direction), texture, &cylinder_table);
	out_cylinder->shape = shape;
	out_cylinder->diameter = diameter;
	out_cylinder->height = height;
}

void	delete_cylinder(void* obj)
{
	free(obj);
}

t_vector2	get_uv_coordinate_in_cylinder(const void* cylinder, \
const t_vector3 hit_point)
{
	t_vector2			uv;
	const t_cylinder*	cy = (t_cylinder *)cylinder;
	const t_vector3		n = subtract_vector3(cy->shape.coordinates, hit_point);
	t_matrix3x3			basis;
	t_vector3			local;

	basis.row[X] = cy->shape.local_basis.row[X];
	basis.row[Y] = cy->shape.local_basis.row[Z];
	basis.row[Z] = multiply_vector3(cy->shape.local_basis.row[Y], -1);
	local.x = dot_product3x3(n, basis.row[X]);
	local.y = dot_product3x3(n, basis.row[Y]);
	local.z = dot_product3x3(n, basis.row[Z]);
	uv.x = (atan2f(local.z, local.x) + PI) / (2 * PI);
	uv.y = (local.y + cy->height / 2) / cy->height;
	if (local.y > cy->height / 2 - 0.01f)
	{
		uv.x = local.x / cy->diameter + 0.5f;
		uv.y = -local.z / cy->diameter + 0.5f;
	}
	else if (local.y < -cy->height / 2 + 0.01f)
	{
		uv.x = -local.x / cy->diameter + 0.5f;
		uv.y = local.z / cy->diameter + 0.5f;
	}
	return (uv);
}

bool	is_hit_cylinder(const t_ray ray, \
const void* obj, t_hit_record* out)
{
	const t_cylinder*			cy = obj;
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
const t_cylinder* cy, const float solution, t_hit_record* out);

extern inline bool	is_hit_cylinder_end_cap(const t_ray ray, \
const t_cylinder* cylinder, t_hit_record* out);

extern inline bool	is_hit_up_cap(const t_ray ray, \
const t_cylinder* cylinder, const t_vector3 up_c, t_hit_record* out);

extern inline bool	is_hit_down_cap(const t_ray ray, \
const t_cylinder* cylinder, const t_vector3 down_c, t_hit_record* out);
