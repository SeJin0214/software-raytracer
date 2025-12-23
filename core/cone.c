/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:53:56 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:57:29 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include "equation.h"
#include "hit_cylinder.h"
#include "ft_math.h"

extern inline bool		is_hit_down_cap_in_cone(const t_ray ray, \
const t_cone* cone, const t_vector3 down_c, t_hit_record* out);

extern inline t_vector3	get_normal_in_cone(const t_vector3 point, \
const t_cone cone);

t_vector2	get_uv_coordinate_in_cone(const void* cone, \
const t_vector3 hit_point)
{
	t_vector2			uv;
	const t_cone*		co = (t_cone *)cone;
	const t_vector3		n = subtract_vector3(co->shape.coordinates, hit_point);
	t_matrix3x3			basis;
	t_vector3			local;

	basis.row[X] = co->shape.local_basis.row[X];
	basis.row[Y] = co->shape.local_basis.row[Z];
	basis.row[Z] = multiply_vector3(co->shape.local_basis.row[Y], -1);
	local.x = dot_product3x3(n, basis.row[X]);
	local.y = dot_product3x3(n, basis.row[Y]);
	local.z = dot_product3x3(n, basis.row[Z]);
	uv.x = (atan2f(local.z, local.x) + PI) / (2 * PI);
	uv.y = (local.y + co->height) / co->height;
	if (local.y > -0.01f)
	{
		uv.x = -local.x / co->diameter + 0.5f;
		uv.y = local.z / co->diameter + 0.5f;
	}
	return (uv);
}

t_cone*	copy_construction_to_cone(const t_cone cone)
{
	t_cone*	result = malloc(sizeof(t_cone));

	result->shape = cone.shape;
	result->shape.is_hit = is_hit_cone;
	result->shape.delete = delete_cone;
	result->shape.get_uv_coordinate = get_uv_coordinate_in_cone;
	result->shape.scale_diameter = update_scale_diameter_cone;
	result->shape.scale_height = update_scale_height_cone;
	result->diameter = cone.diameter;
	result->height = cone.height;
	return (result);
}

void	delete_cone(void* obj)
{
	free(obj);
}

bool	is_hit_cone(const t_ray ray, \
const void* obj, t_hit_record* out)
{
	const t_cone*				co = obj;
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
	h = calculate_hit_height(ray, co->shape.local_basis.row[Z], co->shape.coordinates, solution);
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
