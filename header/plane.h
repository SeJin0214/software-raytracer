/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:28:16 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:05:24 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_BONUS_H
# define PLANE_BONUS_H
# include "solid_shape.h"

typedef struct s_plane
{
	t_shape	shape;
}	t_plane;

/* plane.c */
void	init_plane(t_plane* plane, const t_vector3 coordinates, \
	const t_ivector3 colors, const t_vector3 direction, const t_image texture);
void		delete_plane(void* obj);
bool		is_hit_plane(const t_ray ray, const void* plane, t_hit_record* out);
t_vector2	get_uv_coordinate_in_plane(const void* plane, const t_vector3 hit_point);

/* plane_action.c */
void		update_scale_diameter_plane(void* plane, \
const t_action action);
void		update_scale_height_plane(void* plane, \
const t_action action);

#endif
