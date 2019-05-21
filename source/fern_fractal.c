/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_fern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 11:24:15 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:39:45 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char		is_in_fern_image(t_frac *frac, t_point p)
{
	int a;
	int b;

	a = (int)(frac->start_y + p.i / frac->scale);
	b = (int)(frac->start_x + p.r / frac->scale) + WIN_X / 2;
	return (a > 0 && a < WIN_Y && b > 0 && b < WIN_X);
}

static t_point	make_decision(char chance, t_point p)
{
	t_point np;

	if (chance < 85)
	{
		np.r = 0.85 * p.r + 0.04 * p.i;
		np.i = -0.04 * p.r + 0.85 * p.i + 1.6;
	}
	else if (chance < 92)
	{
		np.r = -0.15 * p.r + 0.28 * p.i;
		np.i = 0.26 * p.r + 0.24 * p.i + 0.44;
	}
	else if (chance < 99)
	{
		np.r = 0.2 * p.r - 0.26 * p.i;
		np.i = 0.23 * p.r + 0.22 * p.i + 1.6;
	}
	else
	{
		np.r = 0;
		np.i = 0.16 * p.i;
	}
	return (np);
}

void			fern(t_frac *frac)
{
	int		i;
	t_point	p;

	i = -1;
	p.i = 0;
	p.r = 0;
	while (++i < frac->max_iterations)
	{
		if (is_in_fern_image(frac, p))
			put_pixel_image(frac,
					(int)(frac->start_x + p.r / frac->scale) + WIN_X / 2,
					(int)(frac->start_y + p.i / frac->scale),
					(frac->colored) ? 0x00ff00 : 0xffffff);
		p = make_decision((char)(rand() % 100), p);
	}
}
