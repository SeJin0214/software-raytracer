/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:35:12 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 01:53:58 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_BONUS_H
# define CAMERA_BONUS_H
# include "matrix.h"
# include "input.h"

typedef struct s_world	t_world;
typedef struct s_canvas	t_canvas;

typedef struct s_camera
{
	t_vector3	coordinates;
	t_matrix3x3	local_basis;
	float		field_of_view;
	float		x_theta;
	float		y_theta;
}	t_camera;

/* camera.c */
void	init_camera(t_world *world, t_canvas *canvas);
void	move_camera(t_camera *camera, const t_action action);
void	rotate_camera(t_camera *camera, const t_action action);

#endif