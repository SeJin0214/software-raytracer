/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:44:26 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:56:22 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_BONUS_H
# define CONE_BONUS_H
# include "solid_shape.h"
# include "solid_shape_getter.h"

typedef struct s_cone
{
	t_solid_shape	shape;
	float			diameter;
	float			height;
}	t_cone;

/* cone.c */
bool	is_hit_cone(const t_ray ray, \
const void *obj, t_hit_record *out);

/* cone_object.c */
t_cone	*copy_construction_to_cone(const t_cone cone);
void	delete_cone(void *obj);

inline t_vector2	get_uv_coordinate_in_cone(const void *cone, \
const t_vector3 hit_point)
{
	t_vector2			uv;
	const t_cone		*co = (t_cone *)cone;
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

/* cone_action.c */
void	update_scale_diameter_cone(void *cone, \
const t_action action);
void	update_scale_height_cone(void *cone, \
const t_action action);

#endif
