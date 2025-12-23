/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:27:10 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:22:26 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_BONUS_H
# define SPHERE_BONUS_H
# include <math.h>
# include "solid_shape.h"
# include "solid_shape_getter.h"

typedef struct s_sphere
{
	t_solid_shape	shape;
	float			diameter;
}	t_sphere;

/* sphere.c */
t_sphere*	init_construction_to_sphere(const t_sphere sphere, t_world* world);
void		delete_sphere(void* obj);
bool		is_hit_sphere(const t_ray ray, const void* sphere, t_hit_record* out);
t_vector2	get_uv_coordinate_in_sphere(const void* sphere, const t_vector3 hit_point);

inline void	set_hit_record_by_sphere(t_hit_record* out, \
const float solution, const t_ray ray, const t_sphere* sphere)
{
	out->t = solution;
	out->point = get_point_in_ray(ray, out->t);
	out->normal = get_normal_at_hit_point(sphere, \
	normalize_vector3(\
	subtract_vector3(out->point, sphere->shape.coordinates)), out->point);
	out->color = get_color_at_hit_point(sphere, out->point);
	out->object = (void *)sphere;
}

/* sphere_action.c */
void		update_scale_diameter_sphere(void* sphere, const t_action action);
void		update_scale_height_sphere(void* sphere, const t_action action);

#endif
