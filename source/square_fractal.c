/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_fern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 11:24:15 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:41:59 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#define DOT_COUNT 8

static t_point	make_decision(t_point p, t_point cp)
{
	t_point np;

	np.r = (p.r + 2 * cp.r) / 3;
	np.i = (p.i + 2 * cp.i) / 3;
	return (np);
}

static void		fill_dots(t_point p[DOT_COUNT])
{
	p[0].i = 10;
	p[0].r = 10;
	p[1].i = 0;
	p[1].r = 10;
	p[2].i = -10;
	p[2].r = 10;
	p[3].i = 10;
	p[3].r = 0;
	p[5].i = -10;
	p[5].r = 0;
	p[6].i = 10;
	p[6].r = -10;
	p[7].i = 0;
	p[7].r = -10;
	p[4].i = -10;
	p[4].r = -10;
}

static void		init_pts(t_frac *frac, t_point p[DOT_COUNT])
{
	short i;

	fill_dots(p);
	i = -1;
	while (++i < DOT_COUNT)
		if (is_in_image(frac, p[i]))
			put_pixel_image(frac,
					(int)(frac->start_x + p[i].r / frac->scale) + WIN_X / 2,
					(int)(frac->start_y + p[i].i / frac->scale) + WIN_Y / 2,
					(frac->colored) ? 0xffff00 : 0xffffff);
}

void			square(t_frac *frac)
{
	int		i;
	t_point	p[DOT_COUNT];
	t_point	cp;

	cp.i = 1;
	cp.r = 1;
	init_pts(frac, p);
	i = -1;
	while (++i < frac->max_iterations)
	{
		if (is_in_image(frac, cp))
			put_pixel_image(frac,
					(int)(frac->start_x + cp.r / frac->scale) + WIN_X / 2,
					(int)(frac->start_y + cp.i / frac->scale) + WIN_Y / 2,
					(frac->colored) ? 0xffff00 : 0xffffff);
		cp = make_decision(cp, p[rand() % DOT_COUNT]);
	}
	return ;
}
