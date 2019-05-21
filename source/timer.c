/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 19:57:13 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:42:03 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int			calc_time(t_frac *frac)
{
	static double	radians = 0;

	radians += (2 * PI / frac->moves_per_sec);
	if (radians > 2 * PI)
		radians -= 2 * PI;
	frac->c_for_julia.r = frac->turn_radius * cos(radians);
	frac->c_for_julia.i = frac->turn_radius * sin(radians);
	mlx_destroy_image(frac->mlx_ptr, frac->img_ptr);
	frac->img_ptr = mlx_new_image(frac->mlx_ptr, WIN_X, WIN_Y);
	fill_image_threads(frac);
	return (0);
}

int			check_time(t_frac *frac)
{
	double			x;

	if (!frac->timed || frac->frac_type != 1)
		return (0);
	x = (double)(clock() - frac->start_time);
	if (x < ONE_SECOND / frac->moves_per_sec)
		return (0);
	calc_time(frac);
	if (frac->cross)
		print_cross(frac);
	mlx_put_image_to_window(frac->mlx_ptr, frac->win_ptr, frac->img_ptr, 0, 0);
	print_info(frac);
	frac->start_time = clock();
	return (0);
}
