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

	t_vector3 coordinates;
	if (try_parse_vector3(attributes[SPHERE_ATTRIBUTE_CENTER], &coordinates) == false)
	{
		return false;
	}

	float diameter;
	if (try_atof(attributes[SPHERE_ATTRIBUTE_DIAMETER], &diameter) == false || diameter < __FLT_EPSILON__)
	{
		return false;
	}

	t_ivector3 colors;
	if (try_parse_color(attributes[SPHERE_ATTRIBUTE_COLORS], &colors) == false)
	{
		return (false);
	}
	t_sphere* sp = malloc(sizeof(t_sphere));
	init_sphere(sp, coordinates, colors, world->texture, diameter);
	world->shapes.add(&world->shapes, &sp);
	return (true);
}

bool	try_add_plane_to_world(const char** attributes, t_world* world)
{
	const bool	is_invalid_format = get_count_to_words(attributes) != PLANE_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[PLANE_ATTRIBUTE_COORDINATES], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[PLANE_ATTRIBUTE_ORIENTATION_VECTOR], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[PLANE_ATTRIBUTE_COLORS], ',') != COLORS_ATTRIBUTE_COUNT;

	if (is_invalid_format)
	{
		return (false);
	}

	t_vector3 coordinates;
	if (try_parse_vector3(attributes[PLANE_ATTRIBUTE_COORDINATES], &coordinates) == false)
	{
		return false;
	}

	t_vector3 direction;
	if (try_parse_vector3(attributes[PLANE_ATTRIBUTE_ORIENTATION_VECTOR], &direction) == false || is_invalid_normalized_vector3(direction))
	{
		return false;
	}

	t_ivector3 colors;
	if (try_parse_color(attributes[PLANE_ATTRIBUTE_COLORS], &colors) == false)
	{
		return (false);
	}
	
	direction = normalize_vector3(direction);

	t_plane* pl = malloc(sizeof(t_plane));
	init_plane(pl, coordinates, colors, direction, world->texture);
	world->shapes.add(&world->shapes, &pl);
	return (true);
}

bool	try_add_cylinder_to_world(const char** attributes, t_world* world)
{
	const bool	is_invalid_format = get_count_to_words(attributes) != CYLINDER_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[CYLINDER_ATTRIBUTE_COORDINATES], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CYLINDER_ATTRIBUTE_NORMALIZED_VECTOR], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CYLINDER_ATTRIBUTE_COLORS], ',') != COLORS_ATTRIBUTE_COUNT;

	if (is_invalid_format)
	{
		return (false);
	}

	t_vector3 coordinates;
	if (try_parse_vector3(attributes[CYLINDER_ATTRIBUTE_COORDINATES], &coordinates) == false)
	{
		return false;
	}

	t_vector3 direction;
	if (try_parse_vector3(attributes[CYLINDER_ATTRIBUTE_NORMALIZED_VECTOR], &direction) == false || is_invalid_normalized_vector3(direction))
	{
		return false;
	}

	float diameter;
	if (try_atof(attributes[CYLINDER_ATTRIBUTE_DIAMETER], &diameter) == false || diameter < __FLT_EPSILON__)
	{
		return false;
	}

	float height;
	if (try_atof(attributes[CYLINDER_ATTRIBUTE_HEIGHT], &height) == false || height < __FLT_EPSILON__)
	{
		return false;
	}

	t_ivector3 colors;
	if (try_parse_color(attributes[CYLINDER_ATTRIBUTE_COLORS], &colors) == false)
	{
		return (false);
	}

	direction = normalize_vector3(direction);

	t_cylinder* cy = malloc(sizeof(t_cylinder));
	init_cylinder(cy, coordinates, colors, direction, world->texture, diameter, height);
	world->shapes.add(&world->shapes, &cy);
	return (true);
}

bool	try_add_cone_to_world(const char** attributes, t_world* world)
{
	const bool	is_invalid_format = get_count_to_words(attributes) != CONE_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[CONE_ATTRIBUTE_COORDINATES], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CONE_ATTRIBUTE_NORMALIZED_VECTOR], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CONE_ATTRIBUTE_COLORS], ',') != COLORS_ATTRIBUTE_COUNT;

	if (is_invalid_format)
	{
		return (false);
	}

	t_vector3 coordinates;
	if (try_parse_vector3(attributes[CONE_ATTRIBUTE_COORDINATES], &coordinates) == false)
	{
		return false;
	}

	t_vector3 direction;
	if (try_parse_vector3(attributes[CONE_ATTRIBUTE_NORMALIZED_VECTOR], &direction) == false || is_invalid_normalized_vector3(direction))
	{
		return false;
	}

	float diameter;
	if (try_atof(attributes[CONE_ATTRIBUTE_DIAMETER], &diameter) == false || diameter < __FLT_EPSILON__)
	{
		return false;
	}

	float height;
	if (try_atof(attributes[CONE_ATTRIBUTE_HEIGHT], &height) == false || height < __FLT_EPSILON__)
	{
		return false;
	}

	t_ivector3 colors;
	if (try_parse_color(attributes[CONE_ATTRIBUTE_COLORS], &colors) == false)
	{
		return (false);
	}

	direction = normalize_vector3(direction);

	t_cone* co = malloc(sizeof(t_cone));
	world->shapes.add(&world->shapes, &co);
	return (true);
}
