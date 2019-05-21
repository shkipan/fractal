/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_fern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 11:24:15 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:39:16 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void		init_pts(t_frac *frac, t_point p[frac->dots_count])
{
	int		i;
	double	radius;

	radius = 5.0;
	i = -1;
	while (++i < frac->dots_count)
	{
		p[i].r = radius * cos(i * 2 * PI / frac->dots_count + PI);
		p[i].i = radius * sin(i * 2 * PI / frac->dots_count + PI);
		if (is_in_image(frac, p[i]))
			put_pixel_image(frac,
					(int)(frac->start_x + p[i].r / frac->scale) + WIN_X / 2,
					(int)(frac->start_y + p[i].i / frac->scale) + WIN_Y / 2,
					(frac->colored) ? 0xff0000 : 0xffffff);
	}
}

static void		calculate_table(t_frac *frac,
		t_point p[frac->dots_count])
{
	int		i;
	int		val;
	t_point	tmp;

	i = -1;
	while (++i < frac->dots_count)
	{
		val = (int)round((double)i * frac->multiply);
		tmp.r = p[i].r;
		tmp.i = p[i].i;
		if (val % frac->dots_count != i)
			draw_line(frac, p[i], p[val % frac->dots_count], tmp);
	}
}

void			circle(t_frac *frac)
{
	t_point	p[frac->dots_count];
	int		i;

	draw_circle(frac, 5.0);
	init_pts(frac, p);
	i = -1;
	calculate_table(frac, p);
}
