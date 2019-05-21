/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 12:25:52 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:40:43 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
**			for yellow-blue output
**			0x212100 | (255 - code)
*/

unsigned int	select_color(t_frac *frac, int iterations)
{
	int				color;
	int				cl;
	double			codage;
	unsigned char	code;

	if (!frac->colored)
	{
		codage = (double)iterations / (double)frac->max_iterations;
		code = (char)(sqrt(codage) * (double)255);
		color = (iterations != frac->max_iterations) ?
			(code | (code << 8) | (code << 16))
			: 0x000000;
		return (color);
	}
	cl = (frac->frac_type == 6) ? 0xFF3F00 : 0x2121FF;
	cl = (frac->frac_type == 1) ? 0x09A550 : cl;
	color = (iterations != frac->max_iterations) ? cl : 0x000000;
	return ((color * iterations) % 0xffffff);
}

static t_point	complex_power(t_frac *frac, t_point z)
{
	unsigned char	i;
	t_point			new_z;
	t_point			rez;

	i = 0;
	z.i = (frac->frac_type == 6) ? fabs(z.i) : z.i;
	z.r = (frac->frac_type == 6) ? fabs(z.r) : z.r;
	rez = z;
	while (++i < frac->dots_count)
	{
		new_z.r = rez.r * z.r - rez.i * z.i;
		new_z.i = rez.r * z.i + rez.i * z.r;
		rez.r = new_z.r;
		rez.i = new_z.i;
	}
	return (rez);
}

unsigned int	calculate_iterations(t_frac *frac, t_point z, t_point c)
{
	t_point	new_z;
	double	module;
	double	limit;
	int		i;

	limit = (frac->frac_type == 6) ? 4.0 : 2.0;
	i = 0;
	while (++i < frac->max_iterations)
	{
		new_z.r = complex_power(frac, z).r + c.r;
		new_z.i = complex_power(frac, z).i + c.i;
		module = new_z.r * new_z.r + new_z.i * new_z.i;
		if (module > limit)
			break ;
		z.r = new_z.r;
		z.i = new_z.i;
	}
	return (select_color(frac, i));
}
