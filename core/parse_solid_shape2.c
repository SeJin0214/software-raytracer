/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_solid_shape2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:37:51 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 20:16:07 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

bool	try_add_cone_to_world(char **attributes, t_world *world)
{
	t_cone		cone;
	t_cone		*co;
	const bool	is_invalid_format = \
	get_count_to_words(attributes) != CONE_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[CONE_ATTRIBUTE_COORDINATES], ',') \
	!= VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CONE_ATTRIBUTE_NORMALIZED_VECTOR], ',') \
	!= VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CONE_ATTRIBUTE_COLORS], ',') \
	!= COLORS_ATTRIBUTE_COUNT;

	if (is_invalid_format || is_invalid_value_in_cone(attributes, &cone))
	{
		return (false);
	}
	cone.shape.local_basis.row[Z] = \
	normalize_vector3(cone.shape.local_basis.row[Z]);
	cone.shape.local_basis = \
	get_local_basis(cone.shape.local_basis.row[Z]);
	cone.shape.texture_type = TEXTURE_BASIC;
	cone.shape.texture = world->texture;
	cone.shape.checkerboard_scale = 10;
	co = copy_construction_to_cone(cone);
	world->solid_shapes.add(&world->solid_shapes, &co);
	return (true);
}

bool	is_invalid_value_in_cone(char **attributes, t_cone *cone)
{
	return (try_parse_vector3(attributes[CONE_ATTRIBUTE_COORDINATES], \
	&cone->shape.coordinates) == false \
	|| try_parse_vector3(attributes[CONE_ATTRIBUTE_NORMALIZED_VECTOR], \
	&cone->shape.local_basis.row[Z]) == false \
	|| is_invalid_normalized_vector3(\
	cone->shape.local_basis.row[Z]) \
	|| try_atof(\
	attributes[CONE_ATTRIBUTE_DIAMETER], &cone->diameter) == false \
	|| cone->diameter < __FLT_EPSILON__ || try_atof(\
	attributes[CONE_ATTRIBUTE_HEIGHT], &cone->height) == false \
	|| cone->height < __FLT_EPSILON__ || try_parse_color(\
	attributes[CONE_ATTRIBUTE_COLORS], &cone->shape.colors) == false);
}
