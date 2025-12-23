/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:54:44 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/22 04:53:55 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "world.h"
#include "light.h"

bool	try_move_light(t_world* world, const int key)
{
	t_action	action;

	if (key == HOME)
		action = ACTION_LIGHT_MOVE_FRONT;
	else if (key == END)
		action = ACTION_LIGHT_MOVE_BACK;
	else if (key == DELETE)
		action = ACTION_LIGHT_MOVE_LEFT;
	else if (key == PGDOWN)
		action = ACTION_LIGHT_MOVE_RIGHT;
	else if (key == BACKSPACE)
		action = ACTION_LIGHT_MOVE_UP;
	else if (key == BACKSLASH)
		action = ACTION_LIGHT_MOVE_DOWN;
	else
		return (false);
	t_light* light = get_element_or_null_in_list(&world->lights, \
	world->current_light_index);
	move_light(light, action);
	return (true);
}

bool	try_change_light(t_world* world, const int key)
{
	if (key == '=')
	{
		if (world->current_light_index == 0)
		{
			world->current_light_index = \
			get_count_in_list(&world->lights) - 1;
		}
		else
		{
			world->current_light_index -= 1;
		}
		return (true);
	}
	else if (key == '-')
	{
		world->current_light_index = \
		(world->current_light_index + 1) \
		% get_count_in_list(&world->lights);
		return (true);
	}
	return (false);
}
