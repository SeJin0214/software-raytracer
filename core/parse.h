/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:20:41 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:06:24 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H
# include "plane.h"
# include "cylinder.h"
# include "cone.h"
# include "world.h"
# define VECTOR_ATTRIBUTE_COUNT 3
# define COLORS_ATTRIBUTE_COUNT 3

typedef struct s_canvas	t_canvas;

typedef enum ambient_attribute
{
	AMBIENT_ATTRIBUTE_RATIO_IN_RANGE = 1,
	AMBIENT_ATTRIBUTE_COLORS,
	AMBIENT_ATTRIBUTE_LENGTH
}	t_ambient_attribute;

typedef enum camera_attribute
{
	CAMERA_ATTRIBUTE_COORDINATES = 1,
	CAMERA_ATTRIBUTE_ORIENTATION_VECTOR,
	CAMERA_ATTRIBUTE_FOV,
	CAMERA_ATTRIBUTE_LENGTH
}	t_camera_attribute;

typedef enum light_attribute
{
	LIGHT_ATTRIBUTE_COORDINATES = 1,
	LIGHT_ATTRIBUTE_RATIO_IN_RANGE,
	LIGHT_ATTRIBUTE_COLORS,
	LIGHT_ATTRIBUTE_LENGTH
}	t_light_attribute;

typedef enum sphere_attribute
{
	SPHERE_ATTRIBUTE_CENTER = 1,
	SPHERE_ATTRIBUTE_DIAMETER,
	SPHERE_ATTRIBUTE_COLORS,
	SPHERE_ATTRIBUTE_LENGTH
}	t_sphere_attribute;

typedef enum plane_attribute
{
	PLANE_ATTRIBUTE_COORDINATES = 1,
	PLANE_ATTRIBUTE_ORIENTATION_VECTOR,
	PLANE_ATTRIBUTE_COLORS,
	PLANE_ATTRIBUTE_LENGTH
}	t_plane_attribute;

typedef enum cylinder_attribute
{
	CYLINDER_ATTRIBUTE_COORDINATES = 1,
	CYLINDER_ATTRIBUTE_NORMALIZED_VECTOR,
	CYLINDER_ATTRIBUTE_DIAMETER,
	CYLINDER_ATTRIBUTE_HEIGHT,
	CYLINDER_ATTRIBUTE_COLORS,
	CYLINDER_ATTRIBUTE_LENGTH
}	t_cylinder_attribute;

typedef enum cone_attribute
{
	CONE_ATTRIBUTE_COORDINATES = 1,
	CONE_ATTRIBUTE_NORMALIZED_VECTOR,
	CONE_ATTRIBUTE_DIAMETER,
	CONE_ATTRIBUTE_HEIGHT,
	CONE_ATTRIBUTE_COLORS,
	CONE_ATTRIBUTE_LENGTH
}	t_cone_attribute;

/* parse.c */
bool	try_parse(int argc, char **argv, t_world *out_world, t_canvas *canvas);
bool	is_valid_file(char *filename);
bool	try_parse_file(char *filename, t_world *out_world, t_canvas *canvas);
bool	try_parse_attributes(char **attributes, \
t_world *out_world, t_canvas *canvas);

/* parse_solid_shape.c */
bool	try_add_sphere_to_world(char **attributes, t_world *world);
bool	try_add_plane_to_world(char **attributes, t_world *world);
bool	is_invalid_value_in_plane(char **attributes, t_plane *plane);
bool	try_add_cylinder_to_world(char **attributes, t_world *world);
bool	is_invalid_value_in_cylinder(char **attributes, t_cylinder *cylinder);

/* parse_solid_shape2.c */
bool	try_add_cone_to_world(char **attributes, t_world *world);
bool	is_invalid_value_in_cone(char **attributes, t_cone *cone);

/* parse_util.c */
bool	try_parse_vector3(char *attribute, t_vector3 *out_result);
bool	try_parse_color(char *attribute, t_ivector3 *out_result);
bool	is_invalid_normalized_vector3(t_vector3 vector);
bool	is_invalid_ratio_in_range(float brightness);
bool	is_invalid_colors(t_ivector3 colors);

#endif