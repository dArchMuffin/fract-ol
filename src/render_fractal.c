/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:30:45 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/23 17:53:56 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*  racourcir set_complexes */
/* reorganiser si 6 fonctions ?  */

#include "../include/fractol.h"
#include <math.h>

double	scale(double unscaled_num, double new_min, double new_max,
		double old_min, double old_max) // a reec.xire
{
	return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min)
		+ new_min);
}

void	set_complexes(int x, int y, t_fractal *f)
{
	f->z.x = 0.0;
	f->z.y = 0.0;
	if (f->fractal_number == 2 || f->fractal_number == 7
		|| f->fractal_number == 1 || f->fractal_number == 9) // burning ship
		// multibrot
	{
		f->c.x = (scale(x, -3, +3, 0, WINSIZE_X) * f->zoom) + f->shift_x;
		f->c.y = (scale(y, -3, +3, 0, WINSIZE_Y) * f->zoom) - f->shift_y;
	}
	else if (f->fractal_number == 3)
	{
		f->c.x = (scale(x, -3, +3, 0, WINSIZE_X) * f->zoom) + f->shift_x;
		f->c.y = (scale(y, +3, -3, 0, WINSIZE_Y) * f->zoom) + f->shift_y;
	}
	else if (f->fractal_number == 4 || f->fractal_number == 5
		|| f->fractal_number == 6 || f->fractal_number == 8) // julia m
	{
		f->z.x = (scale(x, -3, +3, 0, WINSIZE_X) * f->zoom) + f->shift_x;
		f->z.y = (scale(y, +3, -3, 0, WINSIZE_Y) * f->zoom) + f->shift_y;
		f->c.x = f->j_x; //-0.8;
		f->c.y = f->j_y; // 0.156;
	}
}

void	debug(t_fractal *f)
{
	#include <stdio.h>
	printf("======================================\n");
	printf("boucle t = %f\nj_x = %Lf\nj_y = %Lf\n", f->t, f->j_x, f->j_y);
	printf("f->zoom = %.20Lf\n", f->zoom);
	printf("a.x = %Lf\n", f->a.x);
	printf("a.y = %Lf\n", f->a.y);
	printf("o.x = %Lf\n", f->o.x);
	printf("o.y = %Lf\n", f->o.y);
	printf("multibrot power %f\n", f->power);
}

void	iterate_on_pixels(t_fractal *f)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINSIZE_Y)
	{
		x = 0;
		while (x < WINSIZE_X)
		{
			set_complexes(x, y, f);
			render_fractal(x, y, f);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img.img_p, 0, 0);
	if (f->debug == 1)
		debug(f);
}

void	bit_shift_rgb(int i, int *color, t_fractal *f)
{
	t_color	colors;
	double	t;

	t = (double)i / f->max_iterations;                   
	/* colors.r = (char)(9 * (1 - t) * t * t * t * t * 255); */
	/* colors.g = (char)(15 * (1 - t) * (1 - t) * t * t * 255); */
	/* colors.b = (char)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255); */
	if (f->red_toggle)
		colors.r = (char)(9 * (1 - t) * t * t * t * t * 255);
	else
		colors.r = 0;
	if (f->green_toggle)
		colors.g = (char)(15 * (1 - t) * (1 - t) * t * t * 255);
	else
		colors.g = 0;
	if (f->blue_toggle)
		colors.b = (char)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	else
		colors.b = 0;
	*color = colors.color;
}

void	render_fractal(int x, int y, t_fractal *f)
{
	int	i;
	int	color;

	i = 0;
	while (i < f->max_iterations)
	{
		calculate_f(f);
		if ((f->z.x * f->z.x) + (f->z.y * f->z.y) > f->escape_value)
		{
			//revoir le mode psyche en entier
			//faire des raccourcis en toggle qui active/desactive le R / G / B dans le bit shift
			if (f->psychedelic_colors == 1)
			{
				f->mu = log(log(norm_complex(f->z))) / log(2); // Mu ?
				color = generate_smooth_color(i, f->mu, f->max_iterations,
						f->modify_color, f->palette_n);
			}
			else
				bit_shift_rgb(i, &color, f);
			colorize_pixel(x, y, &f->mlx.img, color);
			return ;
		}
		i++;
	}
	colorize_pixel(x, y, &f->mlx.img, BLACK);
}
