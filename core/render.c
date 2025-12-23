/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:28:55 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/19 21:36:51 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"
#include "float.h"
#include "shadow.h"

extern inline t_ivector3	trace_reflection_color(const t_world* world, \
const t_ray ray, const t_hit_record hit_record, size_t depth);
extern inline t_ivector3	load_hit_point_color(const t_world* world, const t_ray ray);
extern inline t_hit_record	load_hit_record(const t_world* world, const t_ray ray);

void	*render(void* obj)
{
	t_renderer	*renderer = obj;

	size_t y = renderer->start_y;
	while (y < renderer->last_y)
	{
		const float y_theta = renderer->world->camera.y_theta;
		const float pitch_degree = lerp(y_theta, -y_theta, (float)y / renderer->canvas->screen.height);
		
		size_t x = renderer->start_x;
		while (x < renderer->last_x)
		{
			const float x_theta = renderer->world->camera.x_theta;
			const float yaw_degrees = lerp(-x_theta, x_theta, (float)x / renderer->canvas->screen.width);
			
			const t_ray ray_mappied_to_pixel = get_ray_mappied_to_pixel(renderer->world->camera, yaw_degrees, pitch_degree);
			const int color = convert_colors(load_hit_point_color(renderer->world, ray_mappied_to_pixel));

			put_color_in_image_frame(renderer, (int)x, (int)y, color);

			++x;
		}
		++y;
	}
	return (0);
}

t_ray	get_ray_mappied_to_pixel(const t_camera camera, \
const float yaw_degree, const float pitch_degree)
{
	const t_vector3 up_scaled = multiply_vector3(camera.local_basis.row[Y], tanf(get_radian(pitch_degree)));
	const t_vector3 right_scaled = multiply_vector3(camera.local_basis.row[X], tanf(get_radian(yaw_degree)));
	const t_vector3 direction = normalize_vector3(add_vector3(camera.local_basis.row[Z], add_vector3(up_scaled, right_scaled)));
	t_ray ray = get_ray(camera.coordinates, direction);
	return (ray);
}

t_ivector3	compute_reflection_lighting_recursive(const t_world* world, \
const t_ray ray, const t_hit_record hit_record, size_t depth)
{
	t_ivector3 total_color = trace_reflection_color(world, ray, hit_record, depth);
	const t_ivector3 ambient_color = load_ambient_color(world->ambient_light, hit_record);
	
	total_color = add_color(total_color, ambient_color);
	size_t i = 0;
	while (i < world->lights.count)
	{
		t_light* light = get_element_or_null_in_list((t_array_list *)(&world->lights), i);
		++i;

		if (is_shadowed_surface(world, *light, hit_record.point, hit_record.object))
		{
			continue;
		}

		const t_ivector3 diffuse_color = load_diffuse_color(*light, hit_record);
		const t_ivector3 specular_color = load_specular_color(ray.origin, *light, hit_record);
		total_color = add_color(total_color, specular_color);
		total_color = add_color(total_color, diffuse_color);
	}
	return (total_color);
}

bool	is_collision(const t_hit_record record)
{
	return (FLT_MAX != record.t);
}

void	put_color_in_image_frame(t_renderer *renderer, const int x, const int y, const int color)
{
	int			*image_frame_buffer;
	const int	offset = renderer->canvas->screen.width * y + x;

	image_frame_buffer = (int *)renderer->canvas->img->data;
	if (x >= 0 && y >= 0 && y < (int)renderer->canvas->screen.height \
			&& x < (int)renderer->canvas->screen.width)
	{
		*(image_frame_buffer + offset) = color;
	}
}
