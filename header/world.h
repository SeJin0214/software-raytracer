/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:08:49 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/26 05:29:09 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_BONUS_H
# define WORLD_BONUS_H
# include <stdalign.h>
# include "array_list.h"
# include "light_struct.h"
# include "camera.h"
# include "image.h"

typedef struct s_canvas	t_canvas;

typedef struct s_world
{
	t_camera		camera;
	bool			is_valid_camera;
	t_ambient_light	ambient_light;
	bool			is_valid_ambient_light;
	t_array_list	lights;
	t_array_list	solid_shapes;
	size_t			current_object_index;
	size_t			current_light_index;
	t_image			texture;
}	t_world;

bool	init_world(t_world* world, t_canvas* canvas);
void	destroy_world(t_world* world, t_canvas* canvas);
bool	try_add_ambient_light_to_world(const char** attributes, t_world* world);
bool	try_add_light_to_world(const char** attributes, t_world* world);
bool	try_add_camera_to_world(const char** attributes, \
t_world* world, t_canvas* canvas);

#endif