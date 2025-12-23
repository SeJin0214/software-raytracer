/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:32:39 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:05:54 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "plane.h"
#include "solid_shape_getter.h"

t_plane	*copy_construction_to_plane(const t_plane plane)
{
	t_plane	*result;

	result = malloc(sizeof(t_plane));
	result->shape = plane.shape;
	result->shape.is_hit = is_hit_plane;
	result->shape.delete = delete_plane;
	result->shape.get_uv_coordinate = get_uv_coordinate_in_plane;
	result->shape.scale_diameter = update_scale_diameter_plane;
	result->shape.scale_height = update_scale_height_plane;
	return (result);
}

void	delete_plane(void* obj)
{
	free(obj);
}

/**
 * N : normal
 * N * (p1 - p2) = 0
 * p2 : camera ray point, O + tD
 * N * (p1 - (O + tD)) = 0
 * Np1 - NO - tND = 0
 * tND = Np1 - NO
 * t = (Np1 - NO) / ND 
 */
bool	is_hit_plane(const t_ray ray, const void* obj, t_hit_record* out)
{
	const t_plane	*plane = obj;
	const t_vector3	n = plane->shape.local_basis.row[Z];
	const float		numerator = dot_product3x3(n, subtract_vector3(plane->shape.coordinates, ray.origin));
	const float		denominator = dot_product3x3(n, ray.direction);

	if (denominator == 0 || numerator / denominator <= 0 || numerator / denominator >= out->t)
	{
		return (false);
	}
	out->t = numerator / denominator;
	out->point = get_point_in_ray(ray, out->t);
	out->normal = get_normal_at_hit_point(plane, n, out->point);
	out->color = get_color_at_hit_point(plane, out->point);
	out->object = (void *)plane;
	return (true);
}

t_vector2	get_uv_coordinate_in_plane(const void* plane, const t_vector3 hit_point)
{
	t_vector2		uv;
	const t_plane*	pl = plane;
	const t_vector3	direction = subtract_vector3(hit_point, pl->shape.coordinates);

	uv.x = dot_product3x3(direction, pl->shape.local_basis.row[X]);
	uv.y = dot_product3x3(direction, pl->shape.local_basis.row[Y]);
	uv.x = uv.x - floor(uv.x);
	uv.y = uv.y - floor(uv.y);
	return (uv);
}
