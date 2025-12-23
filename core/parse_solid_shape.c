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

bool	try_add_sphere_to_world(const char** attributes, t_world* world)
{
	const bool	is_invalid_format = get_count_to_words(attributes) != SPHERE_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[SPHERE_ATTRIBUTE_CENTER], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[SPHERE_ATTRIBUTE_COLORS], ',') != COLORS_ATTRIBUTE_COUNT;
	if (is_invalid_format)
	{
		return (false);
	}

	t_sphere sphere;

	const bool	is_invalid_value = try_parse_vector3(attributes[SPHERE_ATTRIBUTE_CENTER], &sphere.shape.coordinates) == false \
	|| try_atof(attributes[SPHERE_ATTRIBUTE_DIAMETER], &sphere.diameter) == false \
	|| sphere.diameter < __FLT_EPSILON__ \
	|| try_parse_color(attributes[SPHERE_ATTRIBUTE_COLORS], &sphere.shape.colors) == false;

	if (is_invalid_value)
	{
		return (false);
	}

	t_sphere* sp = init_construction_to_sphere(sphere, world);
	world->solid_shapes.add(&world->solid_shapes, &sp);
	return (true);
}

bool	try_add_plane_to_world(const char** attributes, t_world* world)
{
	const bool	is_invalid_format = get_count_to_words(attributes) != PLANE_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[PLANE_ATTRIBUTE_COORDINATES], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[PLANE_ATTRIBUTE_ORIENTATION_VECTOR], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[PLANE_ATTRIBUTE_COLORS], ',') != COLORS_ATTRIBUTE_COUNT;

	t_plane plane;
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
	
	t_plane* pl = copy_construction_to_plane(plane);
	world->solid_shapes.add(&world->solid_shapes, &pl);
	return (true);
}

bool	is_invalid_value_in_plane(const char** attributes, t_plane* plane)
{
	const bool	is_converted_coordinate = try_parse_vector3(\
	attributes[PLANE_ATTRIBUTE_COORDINATES], &plane->shape.coordinates);
	const bool	is_converted_normalized_orientation_vector = try_parse_vector3(\
	attributes[PLANE_ATTRIBUTE_ORIENTATION_VECTOR], &plane->shape.local_basis.row[Z]);
	const bool	is_converted_color = try_parse_color(attributes[PLANE_ATTRIBUTE_COLORS], &plane->shape.colors);

	return (is_converted_coordinate == false \
	|| is_converted_normalized_orientation_vector == false \
	|| is_invalid_normalized_vector3(plane->shape.local_basis.row[Z]) \
	|| is_converted_color == false);
}

bool	try_add_cylinder_to_world(const char** attributes, t_world* world)
{
	const bool	is_invalid_format = get_count_to_words(attributes) != CYLINDER_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[CYLINDER_ATTRIBUTE_COORDINATES], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CYLINDER_ATTRIBUTE_NORMALIZED_VECTOR], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CYLINDER_ATTRIBUTE_COLORS], ',') != COLORS_ATTRIBUTE_COUNT;

	t_cylinder	cylinder;
	if (is_invalid_format || is_invalid_value_in_cylinder(attributes, &cylinder))
	{
		return (false);
	}

	cylinder.shape.local_basis.row[Z] = \
	normalize_vector3(cylinder.shape.local_basis.row[Z]);
	cylinder.shape.local_basis = \
	get_local_basis(cylinder.shape.local_basis.row[Z]);
	cylinder.shape.texture_type = TEXTURE_BASIC;
	cylinder.shape.texture = world->texture;
	cylinder.shape.checkerboard_scale = 20;

	t_cylinder* cy = copy_construction_to_cylinder(cylinder);
	world->solid_shapes.add(&world->solid_shapes, &cy);
	return (true);
}

bool	is_invalid_value_in_cylinder(const char** attributes, t_cylinder* cylinder)
{
	return (try_parse_vector3(attributes[CYLINDER_ATTRIBUTE_COORDINATES], &cylinder->shape.coordinates) == false \
	|| try_parse_vector3(attributes[CYLINDER_ATTRIBUTE_NORMALIZED_VECTOR], &cylinder->shape.local_basis.row[Z]) == false \
	|| is_invalid_normalized_vector3(cylinder->shape.local_basis.row[Z]) \
	|| try_atof(attributes[CYLINDER_ATTRIBUTE_DIAMETER], &cylinder->diameter) == false \
	|| cylinder->diameter < __FLT_EPSILON__ \
	|| try_atof(attributes[CYLINDER_ATTRIBUTE_HEIGHT], &cylinder->height) == false \
	|| cylinder->height < __FLT_EPSILON__ \
	|| try_parse_color(attributes[CYLINDER_ATTRIBUTE_COLORS], &cylinder->shape.colors) == false);
}

bool	try_add_cone_to_world(const char** attributes, t_world* world)
{
	const bool	is_invalid_format = get_count_to_words(attributes) != CONE_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[CONE_ATTRIBUTE_COORDINATES], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CONE_ATTRIBUTE_NORMALIZED_VECTOR], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CONE_ATTRIBUTE_COLORS], ',') != COLORS_ATTRIBUTE_COUNT;

	t_cone cone;
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

	t_cone* co = copy_construction_to_cone(cone);
	world->solid_shapes.add(&world->solid_shapes, &co);
	return (true);
}

bool	is_invalid_value_in_cone(const char** attributes, t_cone* cone)
{
	return (try_parse_vector3(attributes[CONE_ATTRIBUTE_COORDINATES], &cone->shape.coordinates) == false \
	|| try_parse_vector3(attributes[CONE_ATTRIBUTE_NORMALIZED_VECTOR], &cone->shape.local_basis.row[Z]) == false \
	|| is_invalid_normalized_vector3(cone->shape.local_basis.row[Z]) \
	|| try_atof(attributes[CONE_ATTRIBUTE_DIAMETER], &cone->diameter) == false \
	|| cone->diameter < __FLT_EPSILON__ \
	|| try_atof(attributes[CONE_ATTRIBUTE_HEIGHT], &cone->height) == false \
	|| cone->height < __FLT_EPSILON__ \
	|| try_parse_color(attributes[CONE_ATTRIBUTE_COLORS], &cone->shape.colors) == false);
}
