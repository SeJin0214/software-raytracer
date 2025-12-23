/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_atof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:16:14 by sejjeong          #+#    #+#             */
/*   Updated: 2025/12/23 23:25:19 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#define INT_MAX_LENGTH 10

static bool		try_convert_int(const char *nums, const int index, \
int *out_integer, int *out_float);
static float	add_place(const float integer_place, float float_place);
static bool		try_atoi_only_digit(const char *nums, int *out_result);

bool	try_atof(const char *nums, float *out_result)
{
	int		i;
	int		j;
	int		out_integer;
	int		out_float;
	float	float_place;

	*out_result = 0.0f;
	i = indexof(nums, '.');
	if (try_convert_int(nums, i, &out_integer, &out_float) == false)
	{
		return (false);
	}
	i = get_digit((long)out_float);
	j = 0;
	float_place = (float)out_float;
	while (j < i)
	{
		float_place /= 10;
		++j;
	}
	*out_result = add_place((float)out_integer, float_place);
	return (true);
}

static bool	try_convert_int(const char *nums, const int index, \
int *out_integer, int *out_float)
{
	char	*integer_place;
	char	*float_place;
	bool	is_succeed_integer;
	bool	is_succedd_float;

	integer_place = NULL;
	float_place = NULL;
	if (index != -1)
	{
		integer_place = ft_strndup_malloc(nums, index);
		float_place = ft_strdup(nums + index + 1);
		is_succeed_integer = try_atoi(integer_place, out_integer);
		is_succedd_float = try_atoi_only_digit(float_place, out_float);
		free(integer_place);
		free(float_place);
	}
	else
	{
		is_succeed_integer = try_atoi(nums, out_integer);
		is_succedd_float = true;
		*out_float = 0;
	}
	return (is_succeed_integer && is_succedd_float);
}

static float	add_place(const float integer_place, float float_place)
{
	float	result;

	if (integer_place < 0)
	{
		float_place *= -1;
	}
	result = integer_place + float_place;
	return (result);
}

static bool	try_atoi_only_digit(const char *nums, int *out_result)
{
	*out_result = 0;
	if (ft_strlen(nums) > INT_MAX_LENGTH)
		return (false);
	if (ft_atol(nums) > INT_MAX)
		return (false);
	while (*nums != '\0')
	{
		if (ft_isdigit(*nums) == false)
		{
			*out_result = 0;
			return (false);
		}
		*out_result = *out_result * 10 + *nums - '0';
		++nums;
	}
	return (true);
}
