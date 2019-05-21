/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:01:20 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:40:34 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	take_key(int key, t_frac *frac)
{
	change_key(key, frac);
	update_screen(frac);
	return (0);
}

static int	take_mouse_click(int key, int mouse_x, int mouse_y, t_frac *frac)
{
	change_mouse(key, (double)mouse_x, (double)mouse_y, frac);
	update_screen(frac);
	return (0);
}

static int	take_mouse_move(int mouse_x, int mouse_y, t_frac *frac)
{
	if (frac->frac_type != 1 || (frac->frac_type == 1 && !frac->clicked))
		return (0);
	frac->c_for_julia.i = (double)(2.0 * mouse_x - WIN_X) / (double)WIN_X;
	frac->c_for_julia.r = (double)(2.0 * mouse_y - WIN_Y) / (double)WIN_Y;
	update_screen(frac);
	return (0);
}

static int	close_krestik(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void		hook_key(t_frac *frac)
{
	mlx_loop_hook(frac->mlx_ptr, check_time, frac);
	mlx_hook(frac->win_ptr, 2, 5, take_key, frac);
	mlx_hook(frac->win_ptr, 4, 5, take_mouse_click, frac);
	mlx_hook(frac->win_ptr, 17, 5, close_krestik, frac);
	mlx_hook(frac->win_ptr, 6, 5, take_mouse_move, frac);
}
