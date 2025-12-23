/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:19:04 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/22 02:26:50 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

bool	try_parse_vector3(char* attribute, t_vector3* out_result)
{
	char	**temp;
	bool	is_succeed_x;
	bool	is_succeed_y;
	bool	is_succeed_z;

	temp = ft_split(attribute, ',');
	is_succeed_x = try_atof(temp[0], &out_result->x);
	is_succeed_y = try_atof(temp[1], &out_result->y);
	is_succeed_z = try_atof(temp[2], &out_result->z);
	clear_words(temp);
	return (is_succeed_x && is_succeed_y && is_succeed_z);
}

bool	try_parse_color(char* attribute, t_ivector3 *out_result)
{
	char		**temp;
	bool		is_succeed_r;
	bool		is_succeed_g;
	bool		is_succeed_b;

	temp = ft_split(attribute, ',');
	is_succeed_r = try_atoi(temp[0], &out_result->x);
	is_succeed_g = try_atoi(temp[1], &out_result->y);
	is_succeed_b = try_atoi(temp[2], &out_result->z);
	clear_words(temp);
	if (is_succeed_r == false || is_succeed_g == false \
	|| is_succeed_b == false || is_invalid_colors(*out_result))
	{
		out_result->x = 0;
		out_result->y = 0;
		out_result->z = 0;
		return (false);
	}
	return (true);
}

bool	is_invalid_normalized_vector3(t_vector3 vector)
{
	return (vector.x > 1.0f || vector.x < -1.0f \
	|| vector.y > 1.0f || vector.y < -1.0f \
	|| vector.z > 1.0f || vector.z < -1.0f);
}

bool	is_invalid_ratio_in_range(float brightness)
{
	return (brightness < 0.0f || brightness > 1.0f);
}

bool	is_invalid_colors(t_ivector3 colors)
{
	return (colors.x > 255 || colors.x < 0 \
	|| colors.y > 255 || colors.y < 0 \
	|| colors.z > 255 || colors.z < 0);
}
