/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:55:54 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/25 22:57:55 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_UTIL_BONUS_H
# define RENDER_UTIL_BONUS_H
# include "vector.h"
# include "ft_math.h"

inline int	convert_colors(const t_ivector3 colors)
{
	return ((colors.x << 16) + (colors.y << 8) + colors.z);
}

inline t_ivector3	convert_color_to_ivec3(const int color)
{
	t_ivector3	result;

	result.x = 0xff & (color >> 16);
	result.y = 0xff & (color >> 8);
	result.z = 0xff & color;
	return (result);
}

inline t_ivector3	add_color(const t_ivector3 color0, const t_ivector3 color1)
{
	t_ivector3	result;

	result.x = get_min(color0.x + color1.x, 255);
	result.y = get_min(color0.y + color1.y, 255);
	result.z = get_min(color0.z + color1.z, 255);
	return (result);
}

#endif
