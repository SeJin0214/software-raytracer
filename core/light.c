/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:49:47 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/24 09:20:22 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "world.h"
#include "render.h"

extern inline t_ivector3	load_diffuse_color(const t_light light, \
const t_hit_record hit_record);

extern inline t_ivector3	load_ambient_color(const t_ambient_light ambient, \
const t_hit_record hit_record);

extern inline t_vector3	get_reflection_vector3(const t_vector3 source, \
const t_hit_record hit_record);

extern inline t_ivector3	load_specular_color(const t_vector3 viewer_postion, \
const t_light light, const t_hit_record hit_record);

void	move_light(t_light* light, const t_action action)
{
	if (action == ACTION_LIGHT_MOVE_UP)
		light->coordinates.y += 1;
	else if (action == ACTION_LIGHT_MOVE_DOWN)
		light->coordinates.y -= 1;
	else if (action == ACTION_LIGHT_MOVE_LEFT)
		light->coordinates.x -= 1;
	else if (action == ACTION_LIGHT_MOVE_RIGHT)
		light->coordinates.x += 1;
	else if (action == ACTION_LIGHT_MOVE_FRONT)
		light->coordinates.z += 1;
	else if (action == ACTION_LIGHT_MOVE_BACK)
		light->coordinates.z -= 1;
}
