/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:22:38 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:52:29 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "equation.h"
#include "vector.h"
#include "cylinder.h"

extern inline t_quadratic_equation	load_hit_cy_equation(const t_ray ray, \
const t_cylinder cylinder);
extern inline t_quadratic_equation	load_hit_cone_equation(const t_ray ray, \
const t_cone cone);
extern inline float					get_quadtatic_root_plus(\
const t_quadratic_equation quadtatic);
extern inline float					get_quadtatic_root_minus(\
const t_quadratic_equation quadtatic);
