/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:08:27 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/26 01:48:15 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_BONUS_H
# define QUATERNION_BONUS_H
# include <matrix.h>
# include "ft_math.h"

typedef struct s_quaternion
{
	float	w;
	float	x;
	float	y;
	float	z;
}	t_quaternion;

inline t_quaternion	get_rotation_quaternion(const t_vector3 v, float degree)
{
	t_quaternion	q;

	q.w = cos(get_radian(degree / 2));
	q.x = v.x * sin(get_radian(degree / 2));
	q.y = v.y * sin(get_radian(degree / 2));
	q.z = v.z * sin(get_radian(degree / 2));
	return (q);
}

t_quaternion	hamilton_product(const t_quaternion q1, const t_quaternion q2);
t_matrix3x3		convert_matrix(const t_quaternion q);
t_quaternion	convert_quaternion(const t_matrix3x3 m);
t_quaternion	convert_quaternion_extension(const t_matrix3x3 m);
t_quaternion	get_quaternion_conjugate(const t_quaternion q);

#endif