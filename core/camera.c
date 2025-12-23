/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:21:41 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/26 20:20:23 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "quaternion.h"
#include "solid_shape.h"

void	init_camera(t_world* world, t_canvas* canvas)
{
	world->camera.local_basis.row[Z] = \
	normalize_vector3(world->camera.local_basis.row[Z]);
	world->camera.local_basis = get_local_basis(\
	world->camera.local_basis.row[Z]);
	world->camera.x_theta = world->camera.field_of_view / 2.0f;
	world->camera.y_theta = world->camera.x_theta * \
	((float)canvas->screen.height / canvas->screen.width);
	world->is_valid_camera = true;
}

void	move_camera(t_camera* camera, const t_action action)
{
	if (action == ACTION_CAMERA_MOVE_UP)
		camera->coordinates = add_vector3(camera->coordinates, \
		camera->local_basis.row[Y]);
	else if (action == ACTION_CAMERA_MOVE_DOWN)
		camera->coordinates = subtract_vector3(camera->coordinates, \
		camera->local_basis.row[Y]);
	else if (action == ACTION_CAMERA_MOVE_LEFT)
		camera->coordinates = subtract_vector3(camera->coordinates, \
		camera->local_basis.row[X]);
	else if (action == ACTION_CAMERA_MOVE_RIGHT)
		camera->coordinates = add_vector3(camera->coordinates, \
		camera->local_basis.row[X]);
	else if (action == ACTION_CAMERA_MOVE_FRONT)
		camera->coordinates = add_vector3(camera->coordinates, \
		camera->local_basis.row[Z]);
	else if (action == ACTION_CAMERA_MOVE_BACK)
		camera->coordinates = subtract_vector3(camera->coordinates, \
		camera->local_basis.row[Z]);
}

void	rotate_camera(t_camera* camera, const t_action action)
{
	t_quaternion q_delta;

	t_quaternion current = convert_quaternion(camera->local_basis);
	if (action == ACTION_X_AXIS_ROTATING_CAMERA_CLOCKWISE)
		q_delta = get_rotation_quaternion(camera->local_basis.row[X], 5);
	else if (action == ACTION_X_AXIS_ROTATING_CAMERA_COUNTERCLOCKWISE)
		q_delta = get_rotation_quaternion(camera->local_basis.row[X], -5);
	else if (action == ACTION_Y_AXIS_ROTATING_CAMERA_CLOCKWISE)
		q_delta = get_rotation_quaternion(camera->local_basis.row[Y], 5);
	else if (action == ACTION_Y_AXIS_ROTATING_CAMERA_COUNTERCLOCKWISE)
		q_delta = get_rotation_quaternion(camera->local_basis.row[Y], -5);
	else if (action == ACTION_Z_AXIS_ROTATING_CAMERA_CLOCKWISE)
		q_delta = get_rotation_quaternion(camera->local_basis.row[Z], 5);
	else if (action == ACTION_Z_AXIS_ROTATING_CAMERA_COUNTERCLOCKWISE)
		q_delta = get_rotation_quaternion(camera->local_basis.row[Z], -5);
	camera->local_basis = convert_matrix(hamilton_product(current, q_delta));
	camera->local_basis.row[X] = normalize_vector3(camera->local_basis.row[X]);
	camera->local_basis.row[Y] = normalize_vector3(camera->local_basis.row[Y]);
	camera->local_basis.row[Z] = normalize_vector3(camera->local_basis.row[Z]);
}
