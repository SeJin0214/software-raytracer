/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_shape.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:16:28 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:53:36 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLID_SHAPE_BONUS_H
# define SOLID_SHAPE_BONUS_H
# include <stdbool.h>
# include <stdalign.h>
# include "hit_record.h"
# include "ray.h"
# include "input.h"
# include "array_list.h"
# include "matrix.h"
# include "image.h"

typedef struct s_world	t_world;

typedef enum texture
{
	TEXTURE_BASIC,
	TEXTURE_CHECKERBOARD,
	TEXTURE_IMAGE
}	t_texture;

typedef struct s_solid_shape
{
	t_vector3	coordinates;
	t_ivector3	colors;
	t_matrix3x3	local_basis;
	t_texture	texture_type;
	t_image		texture;
	float		checkerboard_scale;
	bool		(*is_hit)(const t_ray, const void *, t_hit_record *);
	t_vector2	(*get_uv_coordinate)(const void *, const t_vector3 hit_point);
	void		(*delete)(void *);
	void		(*scale_height)(void *, const t_action);
	void		(*scale_diameter)(void *, const t_action);
}	t_solid_shape;

/* solid_shape.c */
void		move_shape(void* obj, const t_action action);
void		rotate_shape(void* obj, const t_action action);
void		set_texcture(void* obj, const t_action action);
void		destroy_shapes(t_array_list *list);
t_matrix3x3	get_local_basis(t_vector3 n);

#endif
