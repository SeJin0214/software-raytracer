/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:13:28 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:02:16 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow.h"
#include "vector.h"

extern inline bool			is_shadowed_surface(const t_world *world, \
const t_light light, const t_vector3 surface, void *object);
extern inline t_ivector3		reflect_light(\
const t_ivector3 ligth_resource_color, const t_ivector3 surface_color);
