/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:20:12 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 17:16:28 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		update_screen(t_frac *frac)
{
	mlx_destroy_image(frac->mlx_ptr, frac->img_ptr);
	frac->img_ptr = mlx_new_image(frac->mlx_ptr, WIN_X, WIN_Y);
	if (frac->frac_type < DEF_FRACTS || frac->frac_type == 6)
		fill_image_threads(frac);
	else
		frac->iterable_function(frac);
	if (frac->cross && (frac->frac_type < DEF_FRACTS || frac->frac_type == 6))
		print_cross(frac);
	mlx_put_image_to_window(frac->mlx_ptr, frac->win_ptr, frac->img_ptr, 0, 0);
	print_info(frac);
}

void		draw_circle(t_frac *frac, double radius)
{
	double	radians;
	t_point	p;

	radians = 0.0;
	while (radians < 2 * PI)
	{
		p.r = radius * cos(radians);
		p.i = radius * sin(radians);
		if (is_in_image(frac, p))
			put_pixel_image(frac,
					(int)(frac->start_x + p.r / frac->scale) + WIN_X / 2,
					(int)(frac->start_y + p.i / frac->scale) + WIN_Y / 2,
					(frac->colored) ? 0xF7B794 : 0xffffff);
		radians += 0.001;
	}
}

void		draw_line(t_frac *frac, t_point p1, t_point p2, t_point x)
{
	t_point d;

	d.r = frac->scale * ((p2.r > p1.r) ? 1 : -1);
	d.i = frac->scale * ((p2.i > p1.i) ? 1 : -1);
	d.r = (ABS(p1.r - p2.r) < 0.01) ? 0 : d.r;
	d.i = (ABS(p1.i - p2.i) < 0.01) ? 0 : d.i;
	if (ABS(p1.r - p2.r) > (float)ABS(p1.i - p2.i))
		d.r *= (ABS(p1.i - p2.i) < 0.01) ? 1 :
			(float)ABS(p1.r - p2.r) / (float)ABS(p1.i - p2.i);
	else
		d.i *= (ABS(p1.r - p2.r) < 0.01) ? 1 :
			(float)ABS(p1.i - p2.i) / (float)ABS(p1.r - p2.r);
	while (ABS(x.r - p1.r) <= ABS(p1.r - p2.r) &&
			ABS(x.i - p1.i) <= ABS(p1.i - p2.i))
	{
		if (is_in_image(frac, x))
			put_pixel_image(frac,
					(int)(frac->start_x + x.r / frac->scale) + WIN_X / 2,
					(int)(frac->start_y + x.i / frac->scale) + WIN_Y / 2,
					(frac->colored) ? 0xFF6BDE : 0xffffff);
		x.r += d.r;
		x.i += d.i;
	}
}

char		is_in_image(t_frac *frac, t_point p)
{
	int a;
	int b;

	a = (int)(frac->start_y + p.i / frac->scale) + WIN_Y / 2;
	b = (int)(frac->start_x + p.r / frac->scale) + WIN_X / 2;
	return (a > 0 && a < WIN_Y && b > 0 && b < WIN_X);
}

void		print_cross(t_frac *frac)
{
	int i;
	int	cl;

	cl = (frac->frac_type == 6 && frac->colored) ? 0x1616AD : 0xFFFF00;
	i = WIN_X / 2 - 31;
	while (++i < WIN_X / 2 + 30)
		put_pixel_image(frac, i, WIN_Y / 2, cl);
	i = WIN_Y / 2 - 31;
	while (++i < WIN_Y / 2 + 30)
		put_pixel_image(frac, WIN_X / 2, i, cl);
}
