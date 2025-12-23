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
	const t_solid_shape	*sh = shape;
	const t_vector2		uv = sh->get_uv_coordinate(sh, hit_point);

	if ((int)floorf((uv.x * sh->checkerboard_scale) \
	+ (int)floorf(uv.y * sh->checkerboard_scale)) % 2 == 0)
	{
		return (get_ivector3(0, 0, 0));
	}
	return (get_ivector3(255, 255, 255));
}

inline t_ivector3	get_texel_color(const void *shape, int x, int y)
{
	const t_solid_shape	*sh = shape;
	const int			offset = sh->texture.width * y + x;
	int					*image_frame_buffer;
	int					color;

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
	const t_solid_shape	*sh = shape;
	const t_vector2		uv = sh->get_uv_coordinate(sh, hit_point);
	const int			x = uv.x * sh->texture.width;
	const int			y = uv.y * sh->texture.height;

	return (get_texel_color(sh, x, y));
}

inline t_ivector3	get_color_at_hit_point(const void *shape, \
const t_vector3 hit_point)
{
	const t_solid_shape	*sh = shape;

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

#endif