/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 19:26:47 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:47:40 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include "../libft/mlx.h"
# include <math.h>
# include <pthread.h>
# include <time.h>
# include <stdio.h>

/*
** stdio for gcvt() to print float numbers on screen
** time for clock() timelapse
*/

# define WIN_X 1000
# define WIN_Y 800
# define THREADS_COUNT 8
# define FRACT_COUNT 7
# define DEF_FRACTS 2
# define PI 3.1416
# define ONE_SECOND (CLOCKS_PER_SEC / 4)

# define RIGHT_SHIFT 300
# define LEFT_SHIFT 20

typedef struct					s_point
{
	double						i;
	double						r;
}								t_point;

typedef struct s_thread_info	t_thread_info;
typedef struct s_frac			t_frac;

struct							s_frac
{
	char						cross;
	char						clicked;
	char						colored;
	char						timed;
	char						usage;
	short						frac_type;
	int							dots_count;
	int							max_iterations;
	int							moves_per_sec;
	double						multiply;
	double						scale;
	double						scale_steps;
	double						start_x;
	double						start_y;
	double						turn_radius;
	t_point						c_for_julia;
	clock_t						start_time;
	void						*img_ptr;
	void						*mlx_ptr;
	void						*win_ptr;
	int							(*fractal_function)(t_thread_info *, int, int);
	void						(*iterable_function)(t_frac *);
};

struct							s_thread_info
{
	int							start_x;
	int							end_x;
	int							color;
	t_frac						*frac;
};

typedef struct					s_fractal
{
	char						*id;
	int							(*t_func)(t_thread_info *, int, int);
	void						(*i_func)(t_frac *);
}								t_fractal;

unsigned int					calculate_iterations(t_frac *frac,
		t_point z, t_point c);
int								check_time(t_frac *frac);

void							fill_image_threads(t_frac *frac);
void							choose_iterable_fracral(t_frac *frac);

void							hook_key(t_frac *frac);
void							error(int code);
void							print_info(t_frac *frac);
void							print_cross(t_frac *frac);
void							reset_params(t_frac *frac);

void							change_key(int key, t_frac *frac);
void							change_mouse(int key, double mouse_x,
		double mouse_y, t_frac *frac);

int								mandelbrot(t_thread_info *info, int i, int j);
int								julia(t_thread_info *info, int i, int j);
void							fern(t_frac *frac);
void							triangle(t_frac *frac);
void							square(t_frac *frac);
void							circle(t_frac *frac);

void							select_fractal(t_frac *frac, char *id);

void							put_pixel_image(t_frac *frac, int x, int y,
		int color);
char							is_in_image(t_frac *frac, t_point p);
void							draw_circle(t_frac *frac, double radius);
void							draw_line(t_frac *frac, t_point p1,
		t_point p2, t_point x);

void							update_screen(t_frac *frac);

#endif
