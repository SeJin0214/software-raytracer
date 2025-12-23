/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:30:46 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/21 17:02:49 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "sphere.h"

void	update_scale_diameter_sphere(void* obj, \
const t_action action)
{
	t_sphere* sphere = obj;

	if (action == ACTION_OBJECT_DIAMETER_SCALE_UP)
	{
		sphere->diameter += 0.5f;
	}
	else if (action == ACTION_OBJECT_DIAMETER_SCALE_DOWN)
	{
		sphere->diameter = fmaxf(sphere->diameter - 0.5f, 0.5f);
	}
}

void	update_scale_height_sphere(void* obj, \
const t_action action)
{
	(void) obj;
	(void) action;
	return ;
}
