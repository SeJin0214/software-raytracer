/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_solid_shape.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:31:31 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 20:16:41 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "sphere.h"

bool	try_add_sphere_to_world(char **attributes, t_world *world)
{
	t_sphere	sphere;
	t_sphere	*sp;
	bool		is_invalid_value;
	const bool	is_invalid_format = \
	get_count_to_words(attributes) != SPHERE_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[SPHERE_ATTRIBUTE_CENTER], ',') \
	!= VECTOR_ATTRIBUTE_COUNT || get_count_words(\
	attributes[SPHERE_ATTRIBUTE_COLORS], ',') != COLORS_ATTRIBUTE_COUNT;

	if (is_invalid_format)
		return (false);
	is_invalid_value = try_parse_vector3(\
	attributes[SPHERE_ATTRIBUTE_CENTER], &sphere.shape.coordinates) == false \
	|| try_atof(attributes[SPHERE_ATTRIBUTE_DIAMETER], &sphere.diameter) == \
	false || sphere.diameter < __FLT_EPSILON__ || try_parse_color(\
	attributes[SPHERE_ATTRIBUTE_COLORS], &sphere.shape.colors) == false;
	if (is_invalid_value)
		return (false);
	sp = init_construction_to_sphere(sphere, world);
	world->solid_shapes.add(&world->solid_shapes, &sp);
	return (true);
}

bool	try_add_plane_to_world(char **attributes, t_world *world)
{
	t_plane		plane;
	t_plane		*pl;
	const bool	is_invalid_format = \
	get_count_to_words(attributes) != PLANE_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[PLANE_ATTRIBUTE_COORDINATES], ',') \
	!= VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[PLANE_ATTRIBUTE_ORIENTATION_VECTOR], ',') \
	!= VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[PLANE_ATTRIBUTE_COLORS], ',') \
	!= COLORS_ATTRIBUTE_COUNT;

	if (is_invalid_format || is_invalid_value_in_plane(attributes, &plane))
	{
		return (false);
	}
	plane.shape.local_basis.row[Z] = \
	normalize_vector3(plane.shape.local_basis.row[Z]);
	plane.shape.local_basis = get_local_basis(plane.shape.local_basis.row[Z]);
	plane.shape.texture_type = TEXTURE_BASIC;
	plane.shape.texture = world->texture;
	plane.shape.checkerboard_scale = 2;
	pl = copy_construction_to_plane(plane);
	world->solid_shapes.add(&world->solid_shapes, &pl);
	return (true);
}

bool	is_invalid_value_in_plane(char **attributes, t_plane *plane)
{
	const bool	is_converted_coordinate = try_parse_vector3(\
	attributes[PLANE_ATTRIBUTE_COORDINATES], &plane->shape.coordinates);
	const bool	is_converted_normalized_orientation_vector = try_parse_vector3(\
	attributes[PLANE_ATTRIBUTE_ORIENTATION_VECTOR], \
	&plane->shape.local_basis.row[Z]);
	const bool	is_converted_color = try_parse_color(\
	attributes[PLANE_ATTRIBUTE_COLORS], &plane->shape.colors);

	return (is_converted_coordinate == false \
	|| is_converted_normalized_orientation_vector == false \
	|| is_invalid_normalized_vector3(\
	plane->shape.local_basis.row[Z]) \
	|| is_converted_color == false);
}

bool	try_add_cylinder_to_world(char **attributes, t_world *world)
{
	t_cylinder	cylinder;
	t_cylinder	*cy;
	const bool	is_invalid_format = \
	get_count_to_words(attributes) != CYLINDER_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[CYLINDER_ATTRIBUTE_COORDINATES], ',') \
	!= VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CYLINDER_ATTRIBUTE_NORMALIZED_VECTOR], ',') \
	!= VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CYLINDER_ATTRIBUTE_COLORS], ',') \
	!= COLORS_ATTRIBUTE_COUNT;

	if (is_invalid_format \
	|| is_invalid_value_in_cylinder(attributes, &cylinder))
		return (false);
	cylinder.shape.local_basis.row[Z] = \
	normalize_vector3(cylinder.shape.local_basis.row[Z]);
	cylinder.shape.local_basis = \
	get_local_basis(cylinder.shape.local_basis.row[Z]);
	cylinder.shape.texture_type = TEXTURE_BASIC;
	cylinder.shape.texture = world->texture;
	cylinder.shape.checkerboard_scale = 20;
	cy = copy_construction_to_cylinder(cylinder);
	world->solid_shapes.add(&world->solid_shapes, &cy);
	return (true);
}

bool	is_invalid_value_in_cylinder(char **attributes, t_cylinder *cylinder)
{
	return (try_parse_vector3(attributes[CYLINDER_ATTRIBUTE_COORDINATES], \
	&cylinder->shape.coordinates) == false \
	|| try_parse_vector3(attributes[CYLINDER_ATTRIBUTE_NORMALIZED_VECTOR], \
	&cylinder->shape.local_basis.row[Z]) == false \
	|| is_invalid_normalized_vector3(\
	cylinder->shape.local_basis.row[Z]) \
	|| try_atof(\
	attributes[CYLINDER_ATTRIBUTE_DIAMETER], &cylinder->diameter) == false \
	|| cylinder->diameter < __FLT_EPSILON__ || try_atof(\
	attributes[CYLINDER_ATTRIBUTE_HEIGHT], &cylinder->height) == false \
	|| cylinder->height < __FLT_EPSILON__ || try_parse_color(\
	attributes[CYLINDER_ATTRIBUTE_COLORS], &cylinder->shape.colors) == false);
}
