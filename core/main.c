/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:08:45 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 20:19:15 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "parse.h"
#include "render.h"

#include <stdint.h>
#include <time.h>
#include "solid_shape.h"

#define MAX_THREAD_SIZE (16)

int	main(int argc, const char** argv)
{
	printf("shape sizeof = %ld\n", sizeof(t_shape));
	t_world		world;
	t_canvas	canvas;
	t_input		input;

	ft_memset(&world, 0, sizeof(t_world));
	init_canvas(&canvas);
	if (try_parse(argc, argv, &world, &canvas) == false)
	{
		printf("Error\n");
		free_canvas(&canvas);
		return (1);
	}
	input.canvas = &canvas;
	input.world = &world;
	render_multi_thread(&world, &canvas);
	mlx_hook(canvas.win, X_BUTTON, 0, mlx_loop_end, canvas.xvar);
	mlx_key_hook(canvas.win, input_key, &input);
	mlx_loop(canvas.xvar);
	destroy_world(&world, &canvas);
	free_canvas(&canvas);
	return (0);
}

int	input_key(int key, t_input *input)
{
	if (key == ESC)
	{
		mlx_loop_end(input->canvas->xvar);
	}
	if (try_move_shape(input->world, key) \
	|| try_rotate_shape(input->world, key) \
	|| try_update_shape_scale(input->world, key) \
	|| try_change_shape(input->world, key) \
	|| try_move_camera(input->world, key) \
	|| try_rotate_camera(input->world, key) \
	|| try_move_light(input->world, key) \
	|| try_change_light(input->world, key) \
	|| try_change_texture(input->world, key))
	{
		render_multi_thread(input->world, input->canvas);
	}
	return (0);
}

static inline uint64_t now_ns(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

void	render_multi_thread(t_world* world, t_canvas* canvas)
{
    uint64_t t0 = now_ns();
	{
		pthread_t	pids[MAX_THREAD_SIZE];
		t_renderer	renderer[MAX_THREAD_SIZE];

		size_t i = 0;
		while (i < MAX_THREAD_SIZE)
		{
			renderer[i].world = world;
			renderer[i].canvas = canvas;
			renderer[i].start_x = canvas->screen.width / 4.0f * (i % 4);
			renderer[i].last_x = canvas->screen.width / 4.0f * (i % 4 + 1);
			renderer[i].start_y = canvas->screen.height / 4.0f * (i / 4);
			renderer[i].last_y = canvas->screen.height / 4.0f * (i / 4 + 1);
			pthread_create(&pids[i], NULL, render, &renderer[i]);
			++i;
		}
		i = 0;
		while (i < MAX_THREAD_SIZE)
		{
			pthread_join(pids[i], NULL);
			++i;
		}
		mlx_put_image_to_window(canvas->xvar, canvas->win, canvas->img, 0, 0);
	}
	uint64_t t1 = now_ns();

    double sec = (double)(t1 - t0) / 1e9;
    printf("render_s=%.6f\n", sec); // 소수점 6자리(마음대로 조절)

}

