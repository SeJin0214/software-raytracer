/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:52:13 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:50:45 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "solid_shape.h"
#include "world.h"

bool	try_move_shape(t_world* world, const int key)
{
	t_solid_shape**	shape;
	t_action		action;

	if (key == 'w')
		action = ACTION_OBJECT_MOVE_FRONT;
	else if (key == 's')
		action = ACTION_OBJECT_MOVE_BACK;
	else if (key == 'a')
		action = ACTION_OBJECT_MOVE_LEFT;
	else if (key == 'd')
		action = ACTION_OBJECT_MOVE_RIGHT;
	else if (key == 'q')
		action = ACTION_OBJECT_MOVE_UP;
	else if (key == 'z')
		action = ACTION_OBJECT_MOVE_DOWN;
	else
		return (false);
	shape = world->solid_shapes.get_element_or_null(\
	&world->solid_shapes, world->current_object_index);
	move_shape(*shape, action);
	return (true);
}

bool	try_rotate_shape(t_world* world, const int key)
{
	t_solid_shape**	shape;
	t_action		action;

	if (key == 'f')
		action = ACTION_Z_AXIS_ROTATING_OBJECT_COUNTERCLOCKWISE;
	else if (key == 'h')
		action = ACTION_Z_AXIS_ROTATING_OBJECT_CLOCKWISE;
	else if (key == 'v')
		action = ACTION_Y_AXIS_ROTATING_OBJECT_CLOCKWISE;
	else if (key == 'n')
		action = ACTION_Y_AXIS_ROTATING_OBJECT_COUNTERCLOCKWISE;
	else if (key == 'g')
		action = ACTION_X_AXIS_ROTATING_OBJECT_COUNTERCLOCKWISE;
	else if (key == 'b')
		action = ACTION_X_AXIS_ROTATING_OBJECT_CLOCKWISE;
	else
		return (false);
	shape = world->solid_shapes.get_element_or_null(\
	&world->solid_shapes, world->current_object_index);
	rotate_shape(*shape, action);
	return (true);
}

bool	try_update_shape_scale(t_world* world, const int key)
{
	t_solid_shape**	shape;
	t_action		action;

	if (key == 'u')
		action = ACTION_OBJECT_DIAMETER_SCALE_UP;
	else if (key == 'j')
		action = ACTION_OBJECT_DIAMETER_SCALE_DOWN;
	else if (key == 'i')
		action = ACTION_OBJECT_HEIGHT_SCALE_UP;
	else if (key == 'k')
		action = ACTION_OBJECT_HEIGHT_SCALE_DOWN;
	else
		return (false);
	shape = world->solid_shapes.get_element_or_null(\
	&world->solid_shapes, world->current_object_index);
	(*shape)->scale_diameter(*shape, action);
	(*shape)->scale_height(*shape, action);
	return (true);
}

bool	try_change_shape(t_world* world, const int key)
{
	if (key == ',')
	{
		if (world->current_object_index == 0)
		{
			world->current_object_index = \
			get_count_in_list(&world->solid_shapes) - 1;
		}
		else
		{
			world->current_object_index -= 1;
		}
		return (true);
	}
	else if (key == '.')
	{
		world->current_object_index = \
		(world->current_object_index + 1) \
		% get_count_in_list(&world->solid_shapes);
		return (true);
	}
	return (false);
}

bool	try_change_texture(t_world* world, const int key)
{
	t_solid_shape**	shape;
	t_action		action;

	if (key == '1')
	{
		action = ACTION_CHANGE_TEXTURE_BASIC;
	}
	else if (key == '2')
	{
		action = ACTION_CHANGE_TEXTURE_CHECKERBOARD;
	}
	else if (key == '3')
	{
		action = ACTION_CHANGE_TEXTURE_IMAGE;
	}
	else
	{
		return (false);
	}
	shape = world->solid_shapes.get_element_or_null(\
	&world->solid_shapes, world->current_object_index);
	set_texcture(*shape, action);
	return (true);
}
