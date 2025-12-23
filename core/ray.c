/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:31:36 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/21 19:51:58 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vector.h"

extern inline t_ray		get_ray(const t_vector3 origin, \
const t_vector3 direction);
extern inline t_vector3	get_point_in_ray(const t_ray ray, const float t);
