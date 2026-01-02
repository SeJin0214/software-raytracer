/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_shape_getter.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:14:03 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:54:58 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLID_SHAPE_GETTER_BONUS_H
# define SOLID_SHAPE_GETTER_BONUS_H
# include "solid_shape.h"
# include "render.h"

inline t_ivector3	get_checkerboard_color_at_hit_point(\
const void *shape, const t_vector3 hit_point)
{
	const t_shape*	sh = shape;
	const t_vector2			uv = sh->vtable->get_uv_coordinate(sh, hit_point);

	if ((int)floorf((uv.x * sh->checkerboard_scale) \
	+ (int)floorf(uv.y * sh->checkerboard_scale)) % 2 == 0)
	{
		return (get_ivector3(0, 0, 0));
	}
	return (get_ivector3(255, 255, 255));
}

inline t_ivector3	get_texel_color(const void *shape, int x, int y)
{
	const t_shape*	sh = shape;
	const int				offset = sh->texture.width * y + x;
	int*					image_frame_buffer;
	int						color;

	if (y < 0 || x < 0 || x >= sh->texture.width || y >= sh->texture.width)
	{
		return (get_ivector3(0, 0, 0));
	}
	image_frame_buffer = (int *)sh->texture.image->data;
	color = *(image_frame_buffer + offset);
	return (convert_color_to_ivec3(color));
}

inline t_ivector3	get_image_color_at_hit_point(\
const void *shape, const t_vector3 hit_point)
{
	const t_shape*	sh = shape;
	const t_vector2			uv = sh->vtable->get_uv_coordinate(sh, hit_point);
	const int				x = uv.x * sh->texture.width;
	const int				y = uv.y * sh->texture.height;

	return (get_texel_color(sh, x, y));
}

inline t_ivector3	get_color_at_hit_point(const void *shape, \
const t_vector3 hit_point)
{
	const t_shape*	sh = shape;

	if (sh->texture_type == TEXTURE_BASIC)
	{
		return (sh->colors);
	}
	else if (sh->texture_type == TEXTURE_CHECKERBOARD)
	{
		return (get_checkerboard_color_at_hit_point(sh, hit_point));
	}
	else if (sh->texture_type == TEXTURE_IMAGE)
	{
		return (get_image_color_at_hit_point(sh, hit_point));
	}
	ft_assert(false, "get_color_at_hit_point, invalid texture type");
	return (sh->colors);
}

inline float	get_height(t_ivector3 color)
{
	return ((color.x + color.y + color.z) / (3.0f * 255.0f));
}

inline t_vector3	get_bump_normal(const void *shape, const t_vector3 n, \
int x, int y)
{
	const float			left_height = get_height(\
	get_texel_color(shape, x - 1, y));
	const float			up_height = get_height(\
	get_texel_color(shape, x, y - 1));
	const float			right_height = get_height(\
	get_texel_color(shape, x + 1, y));
	const float			down_height = get_height(\
	get_texel_color(shape, x, y + 1));
	const t_vector3		normal = normalize_vector3(\
	get_vector3(right_height - left_height, down_height - up_height, \
	sqrtf(1.0f - powf(right_height - left_height, 2) \
	- powf(down_height - up_height, 2))));

	return (normalize_vector3(multiply_vector_and_matrix3x3(normal, \
	get_local_basis(n))));
}

inline t_vector3	get_normal_at_hit_point(const void *shape, \
const t_vector3 n, const t_vector3 hit_point)
{
	const t_shape*	sh = (t_shape *)shape;
	t_vector2				uv;
	t_ivector2				xy;

	if (sh->texture_type == TEXTURE_BASIC \
	|| sh->texture_type == TEXTURE_CHECKERBOARD)
	{
		return (n);
	}
	else if (sh->texture_type == TEXTURE_IMAGE)
	{
		uv = sh->vtable->get_uv_coordinate(sh, hit_point);
		xy.x = uv.x * sh->texture.width;
		xy.y = uv.y * sh->texture.height;
		return (get_bump_normal(shape, n, xy.x, xy.y));
	}
	ft_assert(false, "invalid texture type");
	return (n);
}


#endif
