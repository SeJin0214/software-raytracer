/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:17:36 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 19:06:09 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "world.h"
#include "parse.h"

bool	try_parse(const int argc, const char** argv, t_world *out_world, t_canvas* canvas)
{
	if (argc != 2 || is_valid_file(argv[1]) == false)
	{
		return (false);
	}

	if (init_world(out_world, canvas) == false \
	|| try_parse_file(argv[1], out_world, canvas) == false \
	|| out_world->is_valid_ambient_light == false \
	|| out_world->is_valid_camera == false \
	|| out_world->lights.get_count(&out_world->lights) == 0)
	{
		destroy_world(out_world, canvas);
		return (false);
	}
	return (true);
}

bool	is_valid_file(const char* filename)
{
	while (*filename != '\0')
	{
		if (ft_strcmp(filename, ".rt") == 0)
		{
			return (true);
		}
		++filename;
	}
	return (false);
}

bool	try_parse_file(const char* filename, t_world *out_world, t_canvas* canvas)
{
	const int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		return (false);
	}

	bool is_succeed = true;
	while (true)
	{
		char* line = get_next_line(fd);
		if (line == NULL)
		{
			break;
		}
		line[ft_strlen(line) - 1] = '\0';

		char** attributes = ft_split(line, ' ');
		if (attributes[0] != NULL)
		{
			is_succeed = try_parse_attributes((const char**)attributes, out_world, canvas);
		}
		clear_words(attributes);
		free(line);
		if (is_succeed == false)
		{
			break;
		}
	}
	close(fd);
	return (is_succeed);
}

bool	try_parse_attributes(const char** attributes, \
t_world *out_world, t_canvas* canvas)
{
	bool	is_succeed;

	if (ft_strcmp(attributes[0], "A") == 0)
		is_succeed = try_add_ambient_light_to_world(attributes, out_world);
	else if (ft_strcmp(attributes[0], "L") == 0)
		is_succeed = try_add_light_to_world(attributes, out_world);
	else if (ft_strcmp(attributes[0], "C") == 0)
		is_succeed = try_add_camera_to_world(attributes, out_world, canvas);
	else if (ft_strcmp(attributes[0], "sp") == 0)
		is_succeed = try_add_sphere_to_world(attributes, out_world);
	else if (ft_strcmp(attributes[0], "pl") == 0)
		is_succeed = try_add_plane_to_world(attributes, out_world);
	else if (ft_strcmp(attributes[0], "cy") == 0)
		is_succeed = try_add_cylinder_to_world(attributes, out_world);
	else if (ft_strcmp(attributes[0], "co") == 0)
		is_succeed = try_add_cone_to_world(attributes, out_world);
	else
		return (false);
	return (is_succeed);
}
