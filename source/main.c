/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 19:18:56 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 17:45:06 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		reset_params(t_frac *frac)
{
	frac->scale = (frac->frac_type < DEF_FRACTS || frac->frac_type == 6)
		? 0.004 : 0.015;
	if (frac->frac_type == 3 || frac->frac_type == 5)
		frac->scale = 0.0225;
	else if (frac->frac_type == 4)
		frac->scale = 0.045;
	else if (frac->frac_type == 6)
		frac->scale = 0.005;
	frac->scale_steps = (frac->frac_type < DEF_FRACTS || frac->frac_type == 6)
		? 0.2 : 0.2;
	frac->start_x = 0.0;
	frac->start_y = 0.0;
	frac->max_iterations =
		(frac->frac_type > DEF_FRACTS - 1 && frac->frac_type < 6) ?
		5000000 : 200;
	if (frac->frac_type == 5)
	{
		frac->dots_count = 100;
		frac->multiply = 2.0;
	}
	else
		frac->dots_count = 2;
	frac->cross = 0;
	frac->clicked = 0;
	frac->timed = 0;
}

void		select_fractal(t_frac *frac, char *id)
{
	int					i;
	static t_fractal	fractals[FRACT_COUNT] = {
		{"1", &mandelbrot, NULL},
		{"2", &julia, NULL},
		{"3", NULL, &fern},
		{"4", NULL, &triangle},
		{"5", NULL, &square},
		{"6", NULL, &circle},
		{"7", &mandelbrot, NULL}
	};

	i = -1;
	frac->frac_type = -1;
	while (++i < FRACT_COUNT)
	{
		if (!ft_strcmp(id, fractals[i].id))
		{
			frac->frac_type = i;
			frac->fractal_function = fractals[i].t_func;
			frac->iterable_function = fractals[i].i_func;
			break ;
		}
	}
	if (frac->frac_type == -1)
		error(2);
}

static void	init_cond(t_frac *frac, char *av)
{
	frac->colored = 0;
	frac->usage = 0;
	frac->timed = 0;
	frac->moves_per_sec = 400;
	frac->turn_radius = 0.7;
	frac->c_for_julia.r = -0.8;
	frac->c_for_julia.i = 0.156;
	srand(time(NULL));
	select_fractal(frac, av);
	reset_params(frac);
	frac->mlx_ptr = mlx_init();
	frac->win_ptr = mlx_new_window(frac->mlx_ptr, WIN_X, WIN_Y, "window");
	frac->img_ptr = mlx_new_image(frac->mlx_ptr, WIN_X, WIN_Y);
	if (frac->frac_type < DEF_FRACTS || frac->frac_type == 6)
		fill_image_threads(frac);
	else
		frac->iterable_function(frac);
	mlx_put_image_to_window(frac->mlx_ptr, frac->win_ptr, frac->img_ptr, 0, 0);
	print_info(frac);
}

int			main(int ac, char **av)
{
	t_frac	frac;

	if (ac != 2)
		error(1);
	init_cond(&frac, av[1]);
	hook_key(&frac);
	mlx_loop(frac.mlx_ptr);
	return (0);
}
