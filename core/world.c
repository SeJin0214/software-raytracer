/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:04:43 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:23:40 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "float.h"
#include "world.h"
#include "solid_shape.h"
#include "parse.h"

bool	init_world(t_world* world, t_canvas* canvas)
{
	int	width;
	int	height;

	world->texture.image = mlx_xpm_file_to_image(canvas->xvar, \
	"texture/earth_col.xpm", &width, &height);
	world->texture.width = width;
	world->texture.height = height;

	world->is_valid_ambient_light = false;
	world->is_valid_camera = false;
	world->current_object_index = 0;
	world->current_light_index = 0;

	init_array_list(&world->solid_shapes, sizeof(t_solid_shape *));
	init_array_list(&world->lights, sizeof(t_light));
	return (world->texture.image != NULL);
}

void	destroy_world(t_world* world, t_canvas* canvas)
{
	if (world->texture.image != NULL)
	{
		mlx_destroy_image(canvas->xvar, world->texture.image);
	}
	destroy_shapes(&world->solid_shapes);
	world->lights.destroy(&world->lights, do_nothing);
}

bool	try_add_ambient_light_to_world(const char** attributes, t_world* world)
{
	const bool	is_invalid_format = get_count_to_words(attributes) != AMBIENT_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[AMBIENT_ATTRIBUTE_COLORS], ',') != COLORS_ATTRIBUTE_COUNT;

	if (is_invalid_format || world->is_valid_ambient_light)
	{
		return (false);
	}

	const bool is_invalid_value = try_atof(attributes[AMBIENT_ATTRIBUTE_RATIO_IN_RANGE], &world->ambient_light.brightness) == false \
	|| is_invalid_ratio_in_range(world->ambient_light.brightness) \
	|| try_parse_color(attributes[AMBIENT_ATTRIBUTE_COLORS], &world->ambient_light.colors) == false;
	if (is_invalid_value)
	{
		return (false);
	}
	
	world->is_valid_ambient_light = true;
	return (true);
}

bool	try_add_camera_to_world(const char** attributes, t_world* world, t_canvas* canvas)
{
	const bool	is_invalid_format = \
	get_count_to_words(attributes) != CAMERA_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[CAMERA_ATTRIBUTE_COORDINATES], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[CAMERA_ATTRIBUTE_ORIENTATION_VECTOR], ',') != VECTOR_ATTRIBUTE_COUNT;

	if (is_invalid_format || world->is_valid_camera)
	{
		return (false);
	}

	const bool is_invalid_value = try_parse_vector3(attributes[CAMERA_ATTRIBUTE_COORDINATES], &world->camera.coordinates) == false \
	|| try_parse_vector3(attributes[CAMERA_ATTRIBUTE_ORIENTATION_VECTOR], &world->camera.local_basis.row[Z]) == false \
	|| try_atof(attributes[CAMERA_ATTRIBUTE_FOV], &world->camera.field_of_view) == false \
	|| world->camera.field_of_view > 180.0f \
	|| world->camera.field_of_view < 0.0f;
	if (is_invalid_value)
	{
		return (false);
	}

	init_camera(world, canvas);
	return (true);
}

bool	try_add_light_to_world(const char** attributes, t_world* world)
{
	const bool	is_invalid_format = get_count_to_words(attributes) != LIGHT_ATTRIBUTE_LENGTH \
	|| get_count_words(attributes[LIGHT_ATTRIBUTE_COORDINATES], ',') != VECTOR_ATTRIBUTE_COUNT \
	|| get_count_words(attributes[LIGHT_ATTRIBUTE_COLORS], ',') != COLORS_ATTRIBUTE_COUNT;

	if (is_invalid_format)
	{
		return (false);
	}

	t_light light;
	const bool is_invalid_value = try_parse_vector3(attributes[LIGHT_ATTRIBUTE_COORDINATES], &light.coordinates) == false \
	|| try_atof(attributes[LIGHT_ATTRIBUTE_RATIO_IN_RANGE], &light.brightness) == false \
	|| is_invalid_ratio_in_range(light.brightness) \
	|| try_parse_color(attributes[LIGHT_ATTRIBUTE_COLORS], &light.colors) == false;
	
	if (is_invalid_value)
	{
		return (false);
	}
	world->lights.add(&world->lights, &light);
	return (true);
}
