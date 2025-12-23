/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 05:18:55 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:57:08 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_BONUS_H
# define IMAGE_BONUS_H
# include "mlx.h"
# include "mlx_int.h"

typedef struct s_image
{
	t_img	*image;
	int		width;
	int		height;
}	t_image;

#endif
