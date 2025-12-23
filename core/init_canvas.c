/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_canvas.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:38:37 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/26 05:28:02 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "canvas.h"
#include "libft.h"
#include "ft_math.h"

void	init_canvas(t_canvas *out_canvas)
{
	const char	*func = "init_canvas";

	out_canvas->xvar = mlx_init();
	if (out_canvas->xvar == NULL)
		exit_by_error(func, "out_canvas->xvar");
	mlx_get_screen_size(out_canvas->xvar, \
			(int *)&out_canvas->screen.width, \
			(int *)&out_canvas->screen.height);
	out_canvas->screen.height = get_min(out_canvas->screen.height, 1000);
	out_canvas->screen.width = 800;
	out_canvas->screen.height = 600;
	out_canvas->win = mlx_new_window(out_canvas->xvar, \
			out_canvas->screen.width, out_canvas->screen.height, "miniRT");
	if (out_canvas->win == NULL)
		exit_by_error(func, "out_canvas->win");
	mlx_clear_window(out_canvas->xvar, out_canvas->win);
	out_canvas->img = init_img(out_canvas);
	mlx_get_data_addr(out_canvas->img, &out_canvas->bit_per_pixel, \
			&out_canvas->line_bit_size, &out_canvas->endian);
}

void	free_canvas(t_canvas *out_canvas)
{
	mlx_destroy_image(out_canvas->xvar, out_canvas->img);
	out_canvas->img = NULL;
	mlx_destroy_window(out_canvas->xvar, out_canvas->win);
	out_canvas->win = NULL;
	mlx_destroy_display(out_canvas->xvar);
	free(out_canvas->xvar);
	out_canvas->xvar = NULL;
}

t_img	*init_img(t_canvas *pa_canvas)
{
	t_img	*img;

	img = mlx_new_image(pa_canvas->xvar, \
			pa_canvas->screen.width, pa_canvas->screen.height);
	if (img == NULL)
	{
		exit_by_error("init_img", "pa_canvas->img");
	}
	return (img);
}
