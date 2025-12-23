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
bool		is_hit_cone(const t_ray ray, const void* obj, t_hit_record* out);
t_vector2	get_uv_coordinate_in_cone(const void* cone, const t_vector3 hit_point);
t_cone*		copy_construction_to_cone(const t_cone cone);
void		delete_cone(void* obj);


inline bool	is_hit_down_cap_in_cone(const t_ray ray, const t_cone* cone, \
const t_vector3 down_c, t_hit_record* out)
{
	const float		numerator = dot_product3x3(cone->shape.local_basis.row[Z], subtract_vector3(down_c, ray.origin));
	const float		denominator = dot_product3x3(cone->shape.local_basis.row[Z], ray.direction);

	if (denominator == 0 || numerator / denominator < 0 || numerator / denominator >= out->t)
	{
		return (false);		
	}
	
	float solution = numerator / denominator;
	t_vector3 p = get_point_in_ray(ray, solution);
	t_vector3 p_sub_c = subtract_vector3(p, down_c);
	if (dot_product3x3(p_sub_c, p_sub_c) > (cone->diameter / 2) * (cone->diameter / 2))
	{
		return (false);
	}

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
	const t_vector3	vectex_to_c = multiply_vector3(cone.shape.local_basis.row[Z], -1);
	const t_vector3	vertex_to_p = \
	normalize_vector3(subtract_vector3(point, \
	add_vector3(cone.shape.coordinates, \
	multiply_vector3(cone.shape.local_basis.row[Z], cone.height))));
	const t_vector3	proj_c = multiply_vector3(vectex_to_c, dot_product3x3(vectex_to_c, vertex_to_p));
	const t_vector3	proj_p = multiply_vector3(vertex_to_p, dot_product3x3(proj_c, vertex_to_p));
	const t_vector3	surface_normal = normalize_vector3(subtract_vector3(proj_c, proj_p));

	return (surface_normal);
}

/* cone_action.c */
void	update_scale_diameter_cone(void* cone, const t_action action);
void	update_scale_height_cone(void* cone, const t_action action);


#endif
