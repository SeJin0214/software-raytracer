/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 05:49:48 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:59:19 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_BONUS_H
# define RENDERER_BONUS_H
# include <pthread.h>

typedef struct s_world	t_world;
typedef struct s_canvas	t_canvas;

typedef struct s_renderer
{
	t_world			*world;
	t_canvas		*canvas;
	size_t			start_x;
	size_t			last_x;
	size_t			start_y;
	size_t			last_y;
	float			y_angle_to_convert;
	float			x_angle_to_convert;
	pthread_mutex_t	canvas_lock;
}	t_renderer;

#endif