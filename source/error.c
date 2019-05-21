/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 19:55:05 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:39:31 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	print_usage(void)
{
	ft_putendl("Usage: ./fractol <fractal_code>");
	ft_putendl("\t1 - mandelbrot");
	ft_putendl("\t2 - julia");
	ft_putendl("\t3 - fern");
	ft_putendl("\t4 - sierpinski triangle");
	ft_putendl("\t5 - sierpinski carpet");
	ft_putendl("\t6 - nefroid");
	ft_putendl("\t7 - burningship");
}

void		error(int code)
{
	if (code == 1)
	{
		ft_putendl("Invalid number of arguments\n");
		print_usage();
	}
	if (code == 2)
	{
		ft_putendl("Invalid fractal code\n");
		print_usage();
	}
	exit(code);
}
