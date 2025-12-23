/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:25:48 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/21 17:04:46 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_RECORD_BONUS_H
# define HIT_RECORD_BONUS_H
# include <limits.h>
# include "vector.h"
# include "libft.h"
# include "float.h"

typedef struct s_hit_record
{
	t_vector3	point;
	t_vector3	normal;
	t_ivector3	color;
	float		t;
	void		*object;
}	t_hit_record;

inline t_hit_record	get_hit_record(void)
{
	t_hit_record	result;

	result.t = FLT_MAX;
	ft_memset(&result.color, INT_MIN, sizeof(t_ivector3));
	ft_memset(&result.point, INT_MIN, sizeof(t_vector3));
	ft_memset(&result.normal, INT_MIN, sizeof(t_vector3));
	return (result);
}

#endif
