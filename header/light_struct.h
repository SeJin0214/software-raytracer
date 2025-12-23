/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 05:07:53 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/22 02:25:41 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_STRUCT_BONUS_H
# define LIGHT_STRUCT_BONUS_H
# include "vector_struct.h"

typedef struct s_ambient_light
{
	float		brightness;
	t_ivector3	colors;
}	t_ambient_light;

typedef struct s_light
{
	t_vector3	coordinates;
	float		brightness;
	t_ivector3	colors;
}	t_light;

#endif
