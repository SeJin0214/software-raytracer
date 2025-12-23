/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:26:13 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:04:34 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H
# include "world.h"
# include "renderer.h"
# include "ray.h"
# include "hit_record.h"
# include "render_util.h"
# include "light.h"
# define PI 3.141592f

/* render.c */
void		render_multi_thread(t_world* world, t_canvas* canvas);
void*		render(void* obj);
bool		is_collision(const t_hit_record record);
t_ivector3	compute_reflection_lighting_recursive(const t_world* world, \
const t_ray ray, const t_hit_record hit_record, size_t depth);
void		put_color_in_image_frame(t_renderer* renderer, const int x, const int y, const int color);
t_ray	get_ray_mappied_to_pixel(const t_camera camera, const float pitch_degrees, const float yaw_degree);

inline t_hit_record	load_hit_record(const t_world* world, const t_ray ray)
{
	size_t			i;
	t_hit_record	hit_record;
	t_solid_shape	**shape;

	i = 0;
	hit_record = get_hit_record();
	while (i < world->solid_shapes.count)
	{
		shape = get_element_or_null_in_list(\
		(t_array_list *)(&world->solid_shapes), i);
		(*shape)->is_hit(ray, *shape, &hit_record);
		++i;
	}
	return (hit_record);
}

inline t_ivector3	load_hit_point_color(const t_world* world, const t_ray ray)
{
	const t_hit_record	hit_record = load_hit_record(world, ray);

	if (is_collision(hit_record) == false)
	{
		return (get_ivector3(0, 0, 0));
	}
	return (compute_reflection_lighting_recursive(world, ray, hit_record, 0));
}

inline t_ivector3	trace_reflection_color(const t_world* world, \
const t_ray ray, const t_hit_record hit_record, size_t depth)
{
	const t_vector3		r = get_reflection_vector3(ray.origin, hit_record);
	const t_ray			reflection = get_ray(add_vector3(hit_record.point, \
	multiply_vector3(r, 0.01f)), r);
	const t_hit_record	next_record = load_hit_record(world, reflection);
	t_ivector3			color;
	t_light				reflection_light;

	if (is_collision(next_record) == false || depth > 5)
	{
		return (get_ivector3(0, 0, 0));
	}
	color = compute_reflection_lighting_recursive(\
	world, reflection, next_record, ++depth);
	reflection_light.colors = color;
	reflection_light.coordinates = next_record.point;
	reflection_light.brightness = 0.5f;
	color = load_diffuse_color(reflection_light, hit_record);
	reflection_light.brightness = 0.5f;
	color = add_color(color, \
	load_specular_color(ray.origin, reflection_light, hit_record));
	return (color);
}

#endif