/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:38:54 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/24 07:55:02 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_BONUS_H
# define LIGHT_BONUS_H
# include "vector.h"
# include "shadow.h"
# include "light_struct.h"

inline t_ivector3	load_ambient_color(const t_ambient_light ambient, const t_hit_record hit_record)
{
	const t_ivector3	reflection_color = reflect_light(ambient.colors, hit_record.color);
	const float			brightness = ambient.brightness;
	const t_ivector3	ambient_color = get_ivector3(brightness * 255, brightness * 255, brightness * 255);
	const t_ivector3	result_color = reflect_light(ambient_color, reflection_color);

	return (result_color);
}

inline t_ivector3	load_diffuse_color(const t_light light, const t_hit_record hit_record)
{
	const t_vector3		surface_to_light = subtract_vector3(light.coordinates, hit_record.point);
	const t_vector3		direction_to_light = normalize_vector3(surface_to_light);
	const float			light_intensity = fmaxf(dot_product3x3(direction_to_light, hit_record.normal), 0.0f);
	const t_ivector3	diffuse_color = multiply_ivector3(multiply_ivector3(light.colors, light_intensity), light.brightness);
	const t_ivector3	result_color = reflect_light(diffuse_color, hit_record.color);

	return (result_color);
}

/**
 * r : reflection_v
 * r = n * 2 * n * l - l
*/
inline t_vector3	get_reflection_vector3(const t_vector3 source, const t_hit_record hit_record)
{
	const t_vector3		surface_to_source = normalize_vector3(subtract_vector3(source, hit_record.point));
	const float			cos = dot_product3x3(hit_record.normal, surface_to_source); // n * l
	const t_vector3		n2 = multiply_vector3(hit_record.normal, 2 * cos); // 2 * n * (n * l)
	const t_vector3		reflection_v = normalize_vector3(subtract_vector3(n2, surface_to_source));

	return (reflection_v);
}

/**
 * (r * v)^sh
*/
inline t_ivector3	load_specular_color(const t_vector3 viewer_postion, \
const t_light light, const t_hit_record hit_record)
{
	const t_vector3		surface_to_viewer = normalize_vector3(subtract_vector3(viewer_postion, hit_record.point));
	const t_vector3		reflection_v = get_reflection_vector3(light.coordinates, hit_record);
	const int 			shininess = 32;
	const float			light_intensity = powf(fmaxf(dot_product3x3(reflection_v, surface_to_viewer), 0.0f), shininess);
	const t_ivector3	specular_color = multiply_ivector3(light.colors, light_intensity);

	return (multiply_ivector3(specular_color, light.brightness));
}

void	move_light(t_light* light, const t_action action);

#endif