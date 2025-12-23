/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_shape_getter2.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:24:43 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:54:12 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLID_SHAPE_GETTER2_BONUS_H
# define SOLID_SHAPE_GETTER2_BONUS_H
# include "vector.h"
# include "solid_shape.h"
# include "solid_shape_getter.h"

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
	const t_solid_shape	*sh = (t_solid_shape *)shape;
	t_vector2			uv;
	t_ivector2			xy;

	if (sh->texture_type == TEXTURE_BASIC \
	|| sh->texture_type == TEXTURE_CHECKERBOARD)
	{
		return (n);
	}
	else if (sh->texture_type == TEXTURE_IMAGE)
	{
		uv = sh->get_uv_coordinate(sh, hit_point);
		xy.x = uv.x * sh->texture.width;
		xy.y = uv.y * sh->texture.height;
		return (get_bump_normal(shape, n, xy.x, xy.y));
	}
	ft_assert(false, "invalid texture type");
	return (n);
}

#endif