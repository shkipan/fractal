/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 13:50:20 by dskrypny          #+#    #+#             */
/*   Updated: 2019/04/30 16:39:53 by dskrypny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		put_pixel_image(t_frac *frac, int x, int y, int color)
{
	int				bpp;
	int				sl;
	int				e;
	char			*res;
	unsigned int	rgb;

	res = mlx_get_data_addr(frac->img_ptr, &bpp, &sl, &e);
	rgb = mlx_get_color_value(frac->mlx_ptr, color);
	ft_memcpy((void *)(res + y * sl + x * bpp / 8), (void *)&rgb, 4);
}

static void	*fill_image(void *threaded_info)
{
	int				i;
	int				j;
	t_thread_info	*info;
	unsigned int	x;

	info = (t_thread_info *)threaded_info;
	i = info->start_x - 1;
	while (++i < info->end_x)
	{
		j = -1;
		while (++j < WIN_Y)
		{
			x = info->frac->fractal_function(info, i, j);
			put_pixel_image(info->frac, i, j, x);
		}
	}
	return (NULL);
}

void		fill_image_threads(t_frac *frac)
{
	int				i;
	pthread_t		threads[THREADS_COUNT];
	t_thread_info	*info[THREADS_COUNT];
	int				wid;

	wid = WIN_X / THREADS_COUNT;
	i = -1;
	while (++i < THREADS_COUNT)
	{
		info[i] = (t_thread_info *)malloc(sizeof(t_thread_info));
		info[i]->start_x = i * wid;
		info[i]->end_x = (i + 1) * wid;
		info[i]->color = i;
		info[i]->frac = frac;
		pthread_create(&(threads[i]), NULL, fill_image, info[i]);
	}
	i = -1;
	while (++i < THREADS_COUNT)
	{
		pthread_join(threads[i], NULL);
		free(info[i]);
	}
}
