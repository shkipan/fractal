/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:59:32 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 17:45:08 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		change_mouse(int key, double mouse_x, double mouse_y, t_frac *frac)
{
	mouse_x += 0;
	mouse_y += 0;
	if (!frac->mlx_ptr)
		return ;
	if (key == 4 || key == 5)
		frac->scale *= 1 - frac->scale_steps * ((key == 5) ? 1 : -1);
	else if (key == 2 && frac->frac_type == 1)
	{
		frac->clicked = 0;
		frac->timed = (frac->timed + 1) % 2;
		frac->start_time = clock();
	}
	else if (key == 1 && frac->frac_type == 1)
	{
		frac->clicked = (frac->clicked + 1) % 2;
		frac->timed = 0;
	}
}

static void	change_fractal(t_frac *frac, int key)
{
	if (key == 18)
		select_fractal(frac, "1");
	else if (key == 19)
		select_fractal(frac, "2");
	else if (key == 20)
		select_fractal(frac, "3");
	else if (key == 21)
		select_fractal(frac, "4");
	else if (key == 23)
		select_fractal(frac, "5");
	else if (key == 22)
		select_fractal(frac, "6");
	else if (key == 26)
		select_fractal(frac, "7");
	reset_params(frac);
}

static void	change_circle_times(t_frac *frac, int key)
{
	if (key == 25 && frac->multiply > 2.0)
		frac->multiply -= 0.1;
	else if (key == 29 && frac->multiply < 100.0)
		frac->multiply += 0.1;
	else if (key == 24 && frac->dots_count < 200)
		frac->dots_count += 1;
	else if (key == 27 && frac->dots_count > 3)
		frac->dots_count -= 1;
}

static void	change_iterations(t_frac *frac, int key)
{
	if (frac->frac_type < DEF_FRACTS || frac->frac_type == 6)
	{
		if (key == 24 && frac->max_iterations < 1000)
			frac->max_iterations += 100;
		else if (key == 27 && frac->max_iterations > 100)
			frac->max_iterations -= 100;
		else if (key == 25 && frac->dots_count > 2)
			frac->dots_count -= 1;
		else if (key == 29 && frac->dots_count < 10)
			frac->dots_count += 1;
	}
	else if (frac->frac_type == 5)
		change_circle_times(frac, key);
	else
	{
		if (key == 24 && frac->max_iterations < 20000000)
			frac->max_iterations += 1000000;
		else if (key == 27 && frac->max_iterations > 1000000)
			frac->max_iterations -= 1000000;
	}
}

void		change_key(int key, t_frac *frac)
{
	if (key == 7)
		frac->cross = (frac->cross + 1) % 2;
	else if (key == 53)
		exit(0);
	else if (key == 0 || key == 2)
		frac->start_x += ((key == 2) ? 1.0 : -1.0)
			* ((frac->frac_type < DEF_FRACTS || frac->frac_type == 6)
					? frac->scale * 10 : 15);
	else if (key == 1 || key == 13)
		frac->start_y += ((key == 1) ? 1.0 : -1.0)
			* ((frac->frac_type < DEF_FRACTS || frac->frac_type == 6)
					? frac->scale * 10 : 15);
	else if (key == 69 || key == 78)
		frac->scale *= 1 - frac->scale_steps * ((key == 69) ? 1 : -1);
	else if (key == 24 || key == 27 || key == 25 || key == 29)
		change_iterations(frac, key);
	else if (key == 8)
		reset_params(frac);
	else if (key > 17 && key < 29 && key != 24 && key != 27)
		change_fractal(frac, key);
	else if (key == 49)
		frac->colored = (frac->colored + 1) % 2;
	else if (key == 32)
		frac->usage = (frac->usage + 1) % 2;
}
