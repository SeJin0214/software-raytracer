/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:25:33 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/21 17:04:16 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_BONUS_H
# define CANVAS_BONUS_H
# include "mlx.h"
# include "mlx_int.h"
# include "vector.h"
# include "screen.h"

typedef struct s_canvas
{
	t_xvar		*xvar;
	t_win_list	*win;
	t_img		*img;
	int			bit_per_pixel;
	int			line_bit_size;
	int			endian;
	t_screen	screen;
}	t_canvas;

void	init_canvas(t_canvas *out_canvas);
void	free_canvas(t_canvas *out_canvas);
t_img	*init_img(t_canvas *pa_canvas);

#endif
