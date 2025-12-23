/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:13:00 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/22 05:28:47 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

extern inline t_quaternion	get_rotation_quaternion(const t_vector3 v, \
float degree);

t_quaternion	hamilton_product(const t_quaternion q1, const t_quaternion q2)
{
	t_quaternion	q;

	q.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	q.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	q.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	q.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (q);
}

t_matrix3x3	convert_matrix(const t_quaternion q)
{
	t_matrix3x3	m;

	m.row_f[0][0] = 1 - 2 * (q.y * q.y + q.z * q.z);
	m.row_f[0][1] = 2 * (q.x * q.y - q.w * q.z);
	m.row_f[0][2] = 2 * (q.x * q.z + q.w * q.y);
	m.row_f[1][0] = 2 * (q.x * q.y + q.w * q.z);
	m.row_f[1][1] = 1 - 2 * (q.x * q.x + q.z * q.z);
	m.row_f[1][2] = 2 * (q.y * q.z - q.w * q.x);
	m.row_f[2][0] = 2 * (q.x * q.z - q.w * q.y);
	m.row_f[2][1] = 2 * (q.y * q.z + q.w * q.x);
	m.row_f[2][2] = 1 - 2 * (q.x * q.x + q.y * q.y);
	return (m);
}

t_quaternion	convert_quaternion(const t_matrix3x3 m)
{
	const float		tr = m.row_f[0][0] + m.row_f[1][1] + m.row_f[2][2];
	float			s;
	t_quaternion	q;

	if (tr > 0)
	{
		s = sqrtf(tr + 1.0f) * 2.0f;
		q.w = 0.25f * s;
		q.x = (m.row_f[1][2] - m.row_f[2][1]) / s;
		q.y = (m.row_f[2][0] - m.row_f[0][2]) / s;
		q.z = (m.row_f[0][1] - m.row_f[1][0]) / s;
		return (get_quaternion_conjugate(q));
	}
	else if ((m.row_f[0][0] > m.row_f[1][1]) \
	&& (m.row_f[0][0] > m.row_f[2][2]))
	{
		s = sqrtf(1.0f + m.row_f[0][0] - m.row_f[1][1] - m.row_f[2][2]) * 2.0f;
		q.w = (m.row_f[1][2] - m.row_f[2][1]) / s;
		q.x = 0.25f * s;
		q.y = (m.row_f[0][1] + m.row_f[1][0]) / s;
		q.z = (m.row_f[0][2] + m.row_f[2][0]) / s;
		return (get_quaternion_conjugate(q));
	}
	return (get_quaternion_conjugate(convert_quaternion_extension(m)));
}

t_quaternion	convert_quaternion_extension(const t_matrix3x3 m)
{
	float			s;
	t_quaternion	q;

	if (m.row_f[1][1] > m.row_f[2][2])
	{
		s = sqrtf(1.0f + m.row_f[1][1] - m.row_f[0][0] - m.row_f[2][2]) * 2.0f;
		q.w = (m.row_f[2][0] - m.row_f[0][2]) / s;
		q.x = (m.row_f[0][1] + m.row_f[1][0]) / s;
		q.y = 0.25f * s;
		q.z = (m.row_f[1][2] + m.row_f[2][1]) / s;
	}
	else
	{
		s = sqrtf(1.0f + m.row_f[2][2] - m.row_f[0][0] - m.row_f[1][1]) * 2.0f;
		q.w = (m.row_f[0][1] - m.row_f[1][0]) / s;
		q.x = (m.row_f[0][2] + m.row_f[2][0]) / s;
		q.y = (m.row_f[1][2] + m.row_f[2][1]) / s;
		q.z = 0.25f * s;
	}
	return (q);
}

t_quaternion	get_quaternion_conjugate(const t_quaternion q)
{
	t_quaternion	result;

	result.w = q.w;
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;
	return (result);
}
