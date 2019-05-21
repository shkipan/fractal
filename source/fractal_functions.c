/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:17:46 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:40:07 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
** for random
*/
#include <stdlib.h>

int		mandelbrot(t_thread_info *info, int i, int j)
{
	t_point			z;
	t_point			c;

	z.r = 0;
	z.i = 0;
	c.i = info->frac->start_y + (float)(j - WIN_Y / 2)
		* info->frac->scale;
	c.r = info->frac->start_x + (float)(i - WIN_X / 2)
		* info->frac->scale;
	return (calculate_iterations(info->frac, z, c));
}

int		julia(t_thread_info *info, int i, int j)
{
	t_point			z;
	t_point			c;

	c.r = info->frac->c_for_julia.r;
	c.i = info->frac->c_for_julia.i;
	z.i = info->frac->start_y + (float)(j - WIN_Y / 2)
		* info->frac->scale;
	z.r = info->frac->start_x + (float)(i - WIN_X / 2)
		* info->frac->scale;
	return (calculate_iterations(info->frac, z, c));
}
