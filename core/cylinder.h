/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 02:39:10 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:51:46 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_BONUS_H
# define CYLINDER_BONUS_H
# include "solid_shape.h"
# include "solid_shape_getter2.h"

typedef struct s_cylinder
{
	t_solid_shape	shape;
	float			diameter;
	float			height;
}	t_cylinder;

/* cylinder_action.c */
void		update_scale_diameter_cylinder(void *cylinder, \
const t_action action);
void		update_scale_height_cylinder(void *cylinder, \
const t_action action);

/* cylinder_object.c */
t_cylinder	*copy_construction_to_cylinder(const t_cylinder cylinder);
void		delete_cylinder(void *obj);

inline t_vector2	get_uv_coordinate_in_cylinder(const void *cylinder, \
const t_vector3 hit_point)
{
	t_vector2			uv;
	const t_cylinder	*cy = (t_cylinder *)cylinder;
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

#endif