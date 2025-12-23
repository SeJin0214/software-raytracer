/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:24:34 by sejjeong          #+#    #+#             */
/*   Updated: 2025/02/28 18:51:50 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_BONUS_H
# define EQUATION_BONUS_H
# include "ray.h"
# include "cylinder.h"
# include "cone.h"

typedef struct s_quadratic_equation
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
}	t_quadratic_equation;

/**
 * O  : camera origin
 * P  : camera Ray -> O + t0D
 * C  : cylinder center
 * N  : cylinder normal
 * F  : P - C,    hypotenuse 
 * G  : (N * F) * N,  perpendicular     (N * (O + t0D - C))
 * r' : F - G,    base
 * r' dot r' = r^2
 * M : O - C
 * M┵ = M - N(M * N)
 * D┴ = D - N(D * N)
 * || (F - G) dot (F - G) ||^2 = r^2
 * || (P - C - G) ||^2 = r^2
 * || ((M + t0D) - N(M + t0D) * N) ||^2 = r^2
 * || (M + t0D - N(N * M) - t0N(N * D)) ||^2 = r^2
 * || (M - N(M * N) + t0(D - N(D * N)) ||^2 = r^2
 * || M┵ + tD┴ ||^2 = r^2
 * (M┵ + tD┴) * (M┵ + tD┴) = r^2
 * (D┴ * D┴)t^2 + 2t(D┴ * M┵) + (M┵ * M┵) - r^2 = 0, 2d
 * a : (D┴ * D┴)
 * b : 2 * (D┴ * M┵)
 * c : (M┵ * M┵) - r^2
 * N * F = height
*/

inline t_quadratic_equation	load_hit_cy_equation(const t_ray ray, const t_cylinder cylinder)
{
	t_quadratic_equation	result;
	const t_vector3			n = cylinder.shape.local_basis.row[Z];
	const t_vector3			m = subtract_vector3(ray.origin, \
	cylinder.shape.coordinates);
	const t_vector3			orthogonal_d = subtract_vector3(ray.direction, \
	multiply_vector3(n, dot_product3x3(ray.direction, n)));
	const t_vector3			orthogonal_m = subtract_vector3(m, \
	multiply_vector3(n, dot_product3x3(m, n)));

	result.a = dot_product3x3(orthogonal_d, orthogonal_d);
	result.b = 2.0f * dot_product3x3(orthogonal_d, orthogonal_m);
	result.c = dot_product3x3(orthogonal_m, orthogonal_m) \
	- (cylinder.diameter / 2) * (cylinder.diameter / 2);
	result.discriminant = result.b * result.b - 4.0f * result.a * result.c;
	return (result);
}

/**
 * O  : camera origin
 * P  : hit point -> O + t0D
 * C  : cone center
 * N  : cone normal
 * r' : base
 * H  : perpendicular
 * h  : cone height
 * r  : radius
 * h - H : h = r' : r
 * h * r' = r(h - H)
 * r' = r(h - (P - C) * N) / h 
 * ((P - C) - (P - C) * N) * ((P - C) - (P - C) * N) = r' ^2
 * 
 * v : O - C
 * d_dot_n = D * N
 * v_dot_n = v * N
 * r_h_ratio = (r / h)^2
 * a = 1 - (1 + r_h_ratio)d_dot_n^2
 * b = 2 * (v * D - d_dot_n * v_dot_n + r_h_ratio * d_dot_n(h - v_dot_n))
 * c = v * v - v_dot_n * v_dot_n - r_h_ratio(h - v_dot_n)^2
*/

typedef struct substitution_map
{
	t_vector3	o;
	t_vector3	d;
	t_vector3	c;
	t_vector3	n;
	t_vector3	v;
	float		d_dot_n;
	float		v_dot_n;
	float		r_h_ratio;
}	t_substitution_map;

inline t_quadratic_equation	load_hit_cone_equation(const t_ray ray, \
const t_cone cone)
{
	t_quadratic_equation	result;
	t_substitution_map		map;

	map.o = ray.origin;
	map.d = ray.direction;
	map.c = cone.shape.coordinates;
	map.n = cone.shape.local_basis.row[Z];
	map.v = subtract_vector3(map.o, map.c);
	map.d_dot_n = dot_product3x3(map.d, map.n);
	map.v_dot_n = dot_product3x3(map.v, map.n);
	map.r_h_ratio = powf(cone.diameter / 2 / cone.height, 2);
	result.a = 1 - (1 + map.r_h_ratio) * map.d_dot_n * map.d_dot_n;
	result.b = 2 * (dot_product3x3(map.v, map.d) - map.d_dot_n \
	* map.v_dot_n + map.r_h_ratio * map.d_dot_n * (cone.height - map.v_dot_n));
	result.c = dot_product3x3(map.v, map.v) - map.v_dot_n * map.v_dot_n \
	- map.r_h_ratio * powf(cone.height - map.v_dot_n, 2);
	result.discriminant = result.b * result.b - 4 * result.a * result.c;
	return (result);
}

inline float	get_quadtatic_root_plus(const t_quadratic_equation quadtatic)
{
	return ((-quadtatic.b + sqrtf(quadtatic.b * quadtatic.b \
	- 4 * quadtatic.a * quadtatic.c)) / (2 * quadtatic.a));
}

inline float	get_quadtatic_root_minus(const t_quadratic_equation quadtatic)
{
	return ((-quadtatic.b - sqrtf(quadtatic.b * quadtatic.b \
	- 4 * quadtatic.a * quadtatic.c)) / (2 * quadtatic.a));
}

#endif
