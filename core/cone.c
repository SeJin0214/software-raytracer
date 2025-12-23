/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:53:56 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:57:29 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"

extern inline t_vector2	get_uv_coordinate_in_cone(const void *cone, \
const t_vector3 hit_point);

t_cone	*copy_construction_to_cone(const t_cone cone)
{
	t_cone	*result;

	result = malloc(sizeof(t_cone));
	result->shape = cone.shape;
	result->shape.is_hit = is_hit_cone;
	result->shape.delete = delete_cone;
	result->shape.get_uv_coordinate = get_uv_coordinate_in_cone;
	result->shape.scale_diameter = update_scale_diameter_cone;
	result->shape.scale_height = update_scale_height_cone;
	result->diameter = cone.diameter;
	result->height = cone.height;
	return (result);
}

void	delete_cone(void *obj)
{
	free(obj);
}
