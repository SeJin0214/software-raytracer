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
# include "solid_shape_getter.h"

typedef struct s_cylinder
{
	t_solid_shape	shape;
	float			diameter;
	float			height;
}	t_cylinder;

/* cylinder_action.c */
void		update_scale_diameter_cylinder(void* cylinder, const t_action action);
void		update_scale_height_cylinder(void* cylinder, const t_action action);

/* cylinder_object.c */
t_cylinder*	copy_construction_to_cylinder(const t_cylinder cylinder);
void		delete_cylinder(void* obj);
t_vector2	get_uv_coordinate_in_cylinder(const void* cylinder, const t_vector3 hit_point);


#endif