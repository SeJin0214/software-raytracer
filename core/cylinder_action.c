/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_action.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:31:11 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/26 15:32:36 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <math.h>
#include "cylinder.h"

void	update_scale_diameter_cylinder(void* obj, \
const t_action action)
{
	t_cylinder*	cylinder = obj;

	if (action == ACTION_OBJECT_DIAMETER_SCALE_UP)
	{
		cylinder->diameter += 0.5f;
	}
	else if (action == ACTION_OBJECT_DIAMETER_SCALE_DOWN)
	{
		cylinder->diameter = fmaxf(cylinder->diameter - 0.5f, 0.5f);
	}
	else
	{
		assert(!"invalid action in update_scale_diameter_cylinder");
	}
}

void	update_scale_height_cylinder(void* obj, \
const t_action action)
{
	t_cylinder*	cylinder = obj;

	if (action == ACTION_OBJECT_HEIGHT_SCALE_UP)
	{
		cylinder->height += 0.5f;
	}
	else if (action == ACTION_OBJECT_HEIGHT_SCALE_DOWN)
	{
		cylinder->height = fmaxf(cylinder->height - 0.5f, 0.5f);
	}
	else
	{
		assert(!"invalid action in update_scale_height_cylinder");
	}
}
