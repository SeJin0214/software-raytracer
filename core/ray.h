/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:31:31 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/24 05:33:50 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_BONUS_H
# define RAY_BONUS_H
# include "vector.h"

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	direction;
}	t_ray;

inline t_ray	get_ray(const t_vector3 origin, const t_vector3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

inline t_vector3	get_point_in_ray(const t_ray ray, const float t)
{
	return (add_vector3(ray.origin, multiply_vector3(ray.direction, t)));
}

#endif
