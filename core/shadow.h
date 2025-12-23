/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:46:48 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/26 00:03:42 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOW_BONUS_H
# define SHADOW_BONUS_H
# include "world.h"
# include "solid_shape.h"

inline bool	is_shadowed_surface(const t_world *world, const t_light light, \
const t_vector3 surface, void *object)
{
	const t_ray		light_ray = get_ray(light.coordinates, \
	normalize_vector3(subtract_vector3(surface, light.coordinates)));
	t_hit_record	hit_record;
	t_solid_shape	**shape;
	int				i;
	const t_vector3	surface_to_light = \
	subtract_vector3(light.coordinates, surface);

	i = -1;
	hit_record = get_hit_record();
	while ((size_t)++i < world->solid_shapes.count)
	{
		shape = get_element_or_null_in_list(\
		(t_array_list *)(&world->solid_shapes), i);
		if (object == *shape)
			continue ;
		if ((*shape)->is_hit(light_ray, *shape, &hit_record) && \
		get_length_squared(subtract_vector3(light.coordinates, \
		add_vector3(surface, normalize_vector3(surface_to_light)))) \
		> get_length_squared(subtract_vector3(hit_record.point, \
		light.coordinates)))
			return (true);
	}
	return (false);
}

inline t_ivector3	reflect_light(const t_ivector3 ligth_resource_color, \
const t_ivector3 surface_color)
{
	const t_ivector3	reflection_color = \
	{{\
		ligth_resource_color.x * surface_color.x / 255, \
		ligth_resource_color.y * surface_color.y / 255, \
		ligth_resource_color.z * surface_color.z / 255, \
	}};

	return (reflection_color);
}

#endif