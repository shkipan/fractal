/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 23:05:48 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 18:09:05 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	print_left_corner(t_frac *frac, double y)
{
	char	s[20];

	gcvt(frac->scale, 3, s);
	mlx_string_put(frac->mlx_ptr, frac->win_ptr, 0, 0, 0xffffff,
			"Scale");
	mlx_string_put(frac->mlx_ptr, frac->win_ptr, 0, 20, 0xffffff, s);
	if (frac->frac_type > 1 && frac->frac_type < 6)
		return ;
	mlx_string_put(frac->mlx_ptr, frac->win_ptr, 0, 50, 0xffffff,
			(frac->clicked || frac->timed) ? "Mouse" : "Center");
	gcvt((frac->clicked || frac->timed) ? frac->c_for_julia.i :
			frac->start_x, 3, s);
	mlx_string_put(frac->mlx_ptr, frac->win_ptr, LEFT_SHIFT, 70, 0xffffff, s);
	mlx_string_put(frac->mlx_ptr, frac->win_ptr, 0, 70, 0xffffff, "r");
	gcvt(y, 3, s);
	mlx_string_put(frac->mlx_ptr, frac->win_ptr, LEFT_SHIFT, 90, 0xffffff, s);
	mlx_string_put(frac->mlx_ptr, frac->win_ptr, 0, 90, 0xffffff, "i");
}

static void	print_left_down(t_frac *frac, char *x, char *y)
{
	char	s[20];

	if (frac->frac_type != 5)
		x = ft_itoa(frac->max_iterations);
	else
		gcvt(frac->multiply, 10, s);
	if (frac->frac_type == 5)
		y = "Multiplier";
	else if (frac->frac_type >= 2 && frac->frac_type < 5)
		y = "Dots count";
	else
		y = "Iterations count";
	mlx_string_put(frac->mlx_ptr, frac->win_ptr, 0, WIN_Y - 80, 0xffffff, y);
	mlx_string_put(frac->mlx_ptr, frac->win_ptr, 0, WIN_Y - 60, 0xffffff,
			(frac->frac_type != 5) ? x : s);
	if (frac->frac_type != 5)
		free(x);
}

static void	print_right_down(t_frac *frac, char *y)
{
	int x;

	x = 10;
	mlx_string_put(frac->mlx_ptr, frac->win_ptr,
			WIN_X - RIGHT_SHIFT, WIN_Y - (x += 20), 0xffffff,
			(frac->frac_type != 5) ? "+- - change iterations count" :
			"+- - change dots count");
	if (frac->frac_type > 1 && frac->frac_type < 5)
		return ;
	mlx_string_put(frac->mlx_ptr, frac->win_ptr, WIN_X - RIGHT_SHIFT,
			WIN_Y - (x += 20), 0xffffff,
			(frac->frac_type != 5) ? "0,9 - change z power" :
			"0,9 - change multiplier");
	if (frac->frac_type < 2 || frac->frac_type > 4)
	{
		y = (frac->frac_type == 5) ? "Dots count" : "z power in formula";
		mlx_string_put(frac->mlx_ptr, frac->win_ptr, 0,
				WIN_Y - 40, 0xffffff, y);
		y = ft_itoa(frac->dots_count);
		mlx_string_put(frac->mlx_ptr, frac->win_ptr, 0,
				WIN_Y - 20, 0xffffff, y);
		free(y);
	}
}

static void	print_usage(t_frac *frac)
{
	if (!frac->usage)
		return ;
	mlx_string_put(frac->mlx_ptr, frac->win_ptr,
			WIN_X - RIGHT_SHIFT, 20, 0xffffff, "WASD - move image");
	mlx_string_put(frac->mlx_ptr, frac->win_ptr,
			WIN_X - RIGHT_SHIFT, 40, 0xffffff, "+-(NUM) or mouse wheel -");
	mlx_string_put(frac->mlx_ptr, frac->win_ptr,
			WIN_X - RIGHT_SHIFT, 60, 0xffffff, "    zoom image in and out");
	mlx_string_put(frac->mlx_ptr, frac->win_ptr,
			WIN_X - RIGHT_SHIFT, 80, 0xffffff, "1..6 - change fractal");
	mlx_string_put(frac->mlx_ptr, frac->win_ptr,
			WIN_X - RIGHT_SHIFT, 100, 0xffffff, "space - toggle color mode");
	mlx_string_put(frac->mlx_ptr, frac->win_ptr,
			WIN_X - RIGHT_SHIFT, 120, 0xffffff, "C - default view");
	if (frac->frac_type < 2 || frac->frac_type == 6)
		mlx_string_put(frac->mlx_ptr, frac->win_ptr,
			WIN_X - RIGHT_SHIFT, 140, 0xffffff, "X - show zoom target");
}

void		print_info(t_frac *frac)
{
	double y;

	y = (frac->clicked || frac->timed) ? frac->c_for_julia.r :
			frac->start_y;
	if (y != 0)
		y *= -1;
	mlx_string_put(frac->mlx_ptr, frac->win_ptr,
			WIN_X - RIGHT_SHIFT, 0, 0xffffff, "U - toggle usage");
	if (!frac->usage)
		return ;
	print_left_corner(frac, y);
	print_left_down(frac, NULL, NULL);
	print_right_down(frac, NULL);
	print_usage(frac);
}
