/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_shape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:49:29 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:01:54 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "libft.h"
#include "world.h"
#include "solid_shape.h"
#include "solid_shape_getter.h"
#include "solid_shape_getter2.h"
#include "vector.h"
#include "quaternion.h"

void	move_shape(void *obj, const t_action action)
{
	t_solid_shape	*shape;

	shape = obj;
	if (action == ACTION_OBJECT_MOVE_UP)
		shape->coordinates = add_vector3(shape->coordinates, \
		shape->local_basis.row[Y]);
	else if (action == ACTION_OBJECT_MOVE_DOWN)
		shape->coordinates = subtract_vector3(shape->coordinates, \
		shape->local_basis.row[Y]);
	else if (action == ACTION_OBJECT_MOVE_LEFT)
		shape->coordinates = subtract_vector3(shape->coordinates, \
		shape->local_basis.row[X]);
	else if (action == ACTION_OBJECT_MOVE_RIGHT)
		shape->coordinates = add_vector3(shape->coordinates, \
		shape->local_basis.row[X]);
	else if (action == ACTION_OBJECT_MOVE_FRONT)
		shape->coordinates = add_vector3(shape->coordinates, \
		shape->local_basis.row[Z]);
	else if (action == ACTION_OBJECT_MOVE_BACK)
		shape->coordinates = subtract_vector3(shape->coordinates, \
		shape->local_basis.row[Z]);
}

void	rotate_shape(void *obj, const t_action action)
{
	t_quaternion	current;
	t_solid_shape	*shape;
	t_quaternion	q_delta;

	shape = obj;
	current = convert_quaternion(shape->local_basis);
	if (action == ACTION_X_AXIS_ROTATING_OBJECT_CLOCKWISE)
		q_delta = get_rotation_quaternion(shape->local_basis.row[X], 5);
	else if (action == ACTION_X_AXIS_ROTATING_OBJECT_COUNTERCLOCKWISE)
		q_delta = get_rotation_quaternion(shape->local_basis.row[X], -5);
	else if (action == ACTION_Y_AXIS_ROTATING_OBJECT_CLOCKWISE)
		q_delta = get_rotation_quaternion(shape->local_basis.row[Y], 5);
	else if (action == ACTION_Y_AXIS_ROTATING_OBJECT_COUNTERCLOCKWISE)
		q_delta = get_rotation_quaternion(shape->local_basis.row[Y], -5);
	else if (action == ACTION_Z_AXIS_ROTATING_OBJECT_CLOCKWISE)
		q_delta = get_rotation_quaternion(shape->local_basis.row[Z], 5);
	else if (action == ACTION_Z_AXIS_ROTATING_OBJECT_COUNTERCLOCKWISE)
		q_delta = get_rotation_quaternion(shape->local_basis.row[Z], -5);
	shape->local_basis = convert_matrix(hamilton_product(current, q_delta));
	shape->local_basis.row[X] = normalize_vector3(shape->local_basis.row[X]);
	shape->local_basis.row[Y] = normalize_vector3(shape->local_basis.row[Y]);
	shape->local_basis.row[Z] = normalize_vector3(shape->local_basis.row[Z]);
}

void	set_texcture(void *obj, const t_action action)
{
	t_solid_shape	*shape;

	shape = obj;
	if (action == ACTION_CHANGE_TEXTURE_BASIC)
		shape->texture_type = TEXTURE_BASIC;
	else if (action == ACTION_CHANGE_TEXTURE_CHECKERBOARD)
		shape->texture_type = TEXTURE_CHECKERBOARD;
	else if (action == ACTION_CHANGE_TEXTURE_IMAGE)
		shape->texture_type = TEXTURE_IMAGE;
}

t_matrix3x3	get_local_basis(t_vector3 n)
{
	t_matrix3x3	result;
	t_vector3	up;

	up = get_vector3(0.0f, 1.0f, 0.0f);
	if (fabsf(n.y) > 0.9f)
	{
		up = get_vector3(1.0f, 0.0f, 0.0f);
	}
	result.row[X] = cross_product3x3(up, n);
	result.row[Y] = cross_product3x3(n, result.row[X]);
	result.row[Z] = n;
	return (result);
}

void	destroy_shapes(t_array_list *list)
{
	size_t			i;
	t_solid_shape	**shape;

	i = 0;
	while (i < list->count)
	{
		shape = list->get_element_or_null(list, i);
		(*shape)->delete((*shape));
		++i;
	}
	free(list->list);
	list->list = NULL;
}

extern inline t_ivector3	get_texel_color(const void *shape, int x, int y);

extern inline t_ivector3	get_color_at_hit_point(\
const void *shape, const t_vector3 hit_point);

extern inline t_vector3	get_normal_at_hit_point(const void *shape, \
const t_vector3 n, const t_vector3 hit_point);

extern inline t_ivector3	get_checkerboard_color_at_hit_point(\
const void *shape, const t_vector3 hit_point);

extern inline t_ivector3	get_image_color_at_hit_point(\
const void *shape, const t_vector3 hit_point);

extern inline float		get_height(t_ivector3 color);

extern inline t_vector3	get_bump_normal(const void *shape, const t_vector3 n, \
int x, int y);
