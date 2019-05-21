/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_fern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 11:24:15 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:42:06 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#define DOT_COUNT 3

static t_point	make_decision(t_point p, t_point cp)
{
	t_point np;

	np.r = (p.r + cp.r) / 2;
	np.i = (p.i + cp.i) / 2;
	return (np);
}

static void		init_pts(t_frac *frac, t_point p[DOT_COUNT])
{
	short i;

	p[0].i = -8.0;
	p[0].r = 0.0;
	p[1].i = 4.0;
	p[1].r = -6.0;
	p[2].i = 4.0;
	p[2].r = 6.0;
	i = -1;
	while (++i < DOT_COUNT)
		if (is_in_image(frac, p[i]))
			put_pixel_image(frac,
					(int)(frac->start_x + p[i].r / frac->scale) + WIN_X / 2,
					(int)(frac->start_y + p[i].i / frac->scale) + WIN_Y / 2,
					(frac->colored) ? 0x21CEFF : 0xffffff);
}

void			triangle(t_frac *frac)
{
	int		i;
	t_point	p[DOT_COUNT];
	t_point	cp;

	cp.i = 0;
	cp.r = 0;
	init_pts(frac, p);
	i = -1;
	while (++i < frac->max_iterations)
	{
		if (is_in_image(frac, cp))
			put_pixel_image(frac,
					(int)(frac->start_x + cp.r / frac->scale) + WIN_X / 2,
					(int)(frac->start_y + cp.i / frac->scale) + WIN_Y / 2,
					(frac->colored) ? 0x21CEFF : 0xffffff);
		cp = make_decision(p[rand() % DOT_COUNT], cp);
	}
	return ;
}
