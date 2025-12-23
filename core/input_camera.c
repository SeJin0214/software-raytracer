/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:30:25 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/22 05:21:38 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "world.h"

bool	try_move_camera(t_world* world, const int key)
{
	t_action	action;

	if (key == ARROW_UP)
		action = ACTION_CAMERA_MOVE_FRONT;
	else if (key == ARROW_DOWN)
		action = ACTION_CAMERA_MOVE_BACK;
	else if (key == ARROW_LEFT)
		action = ACTION_CAMERA_MOVE_LEFT;
	else if (key == ARROW_RIGHT)
		action = ACTION_CAMERA_MOVE_RIGHT;
	else if (key == RIGHT_SHIFT)
		action = ACTION_CAMERA_MOVE_UP;
	else if (key == RIGHT_CTRL)
		action = ACTION_CAMERA_MOVE_DOWN;
	else
		return (false);
	move_camera(&world->camera, action);
	return (true);
}

bool	try_rotate_camera(t_world* world, const int key)
{
	t_action	action;

	if (key == TENKEY_4)
		action = ACTION_Z_AXIS_ROTATING_CAMERA_COUNTERCLOCKWISE;
	else if (key == TENKEY_6)
		action = ACTION_Z_AXIS_ROTATING_CAMERA_CLOCKWISE;
	else if (key == TENKEY_1)
		action = ACTION_Y_AXIS_ROTATING_CAMERA_CLOCKWISE;
	else if (key == TENKEY_3)
		action = ACTION_Y_AXIS_ROTATING_CAMERA_COUNTERCLOCKWISE;
	else if (key == TENKEY_5)
		action = ACTION_X_AXIS_ROTATING_CAMERA_COUNTERCLOCKWISE;
	else if (key == TENKEY_2)
		action = ACTION_X_AXIS_ROTATING_CAMERA_CLOCKWISE;
	else
		return (false);
	rotate_camera(&world->camera, action);
	return (true);
}
