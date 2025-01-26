/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_inputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:53:43 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/23 17:53:45 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
#include <math.h>
#include <stdio.h> //remplacer par ft_printf

int	arrows(int key, t_fractal *f)
{
	if (key == RIGHT)
		f->shift_x += (0.2 * f->zoom);
	else if (key == LEFT)
		f->shift_x -= (0.2 * f->zoom);
	else if (key == DOWN)
	{
		if (f->bind_combo == 1)
			f->zoom *= 0.7;
		else
			f->shift_y -= (0.2 * f->zoom);
	}
	else if (key == UP)
	{
		if (f->bind_combo == 1)
			f->zoom *= 1.3;
		else
			f->shift_y += (0.2 * f->zoom);
	}
	return (key);
}

int	pav_num_enter(int key, t_fractal *f)
{
	if (key == NUM_ENTER)
	{
		if (f->bind_combo == 1)
		{
			f->max_iterations = 20;
			f->switch_iterations = 20; // a virer du coup ?
		}
		else
			f->max_iterations = f->switch_iterations; // revoir le nom
		printf("max_iterations = %f\n", f->max_iterations);
	}
	return (key);
}

int	pav_num_operators(int key, t_fractal *f)
{
	if (key == PLUS && f->bind_combo == 1 && f->bind_combo_t == 0)
	{
		f->modify_color += 1;
		if (f->debug == 1)
			printf("color modify : %f\n", f->modify_color);
	}
	else if (key == PLUS && f->bind_combo == 0 && f->bind_combo_t == 0)
	{
		f->switch_iterations += 1;
		printf("iterations switch = %d\n", f->switch_iterations); // A VIRER !!!
	}
	else if (key == MINUS && f->bind_combo == 1 && f->bind_combo_t == 0)
		f->modify_color -= 1;
	else if (key == MINUS && f->switch_iterations > 1 && f->bind_combo == 0
		&& f->bind_combo_t == 0)
	{
		f->switch_iterations -= 1;
		printf("iterations switch = %d\n", f->switch_iterations);
	}
	pav_num_enter(key, f);
	return (key);
}

void	num_fractal_switch(int key, t_fractal *f)
{
	if (key >= 49 && key <= 55) // de 1
	{
		f->shift_x = 0.0;
		f->shift_y = 0.0;
		f->zoom = 1.0;
		f->fractal_number = 1;
		/* if (f->fractal_number != 1)
			//on voudrait reset les power quand on appuie sur 1/! */
		f->power = 2;
		if (f->fractal_number != key - '0')
			f->fractal_number = key - '0';
		if (f->fractal_number != 8 && key == 55)
		{
			f->fractal_number = 8;
			if (f->power == 2)
				f->power++;
		}
	}
}

void	color_shift(int key, t_fractal *f) // renommer
{
	if (key == R)
	{
		if (f->psychedelic_colors == 1)
		{
			f->modify_color = 0;
			f->palette_n = 0;
		}
		else 
		{
			if (f->red_toggle == 0)
				f->red_toggle = 1;
			else
				f->red_toggle = 0;
		}
	}
	else if (key == G)
	{
		if (f->psychedelic_colors == 1)
		{
			f->modify_color = 0;
			f->palette_n = 2;
		}
		else
		{
			if (f->green_toggle == 0)
				f->green_toggle = 1;
			else
				f->green_toggle = 0;
		}
	}
	else if (key == B)
	{
		if (f->psychedelic_colors == 1)
		{
			f->modify_color = 0;
			f->palette_n = 1;
		}
		else
		{
			if (f->blue_toggle == 0)
				f->blue_toggle = 1;
			else
				f->blue_toggle = 0;
		}
	}
	else if (key == E) // E
	{
		if (f->psychedelic_colors == 0)
			f->psychedelic_colors = 1;
		else
			f->psychedelic_colors = 0;
	}
}

void	multibrot_power_switch(int key, t_fractal *f)
{
	if (key == 61 && (f->fractal_number == 1 || f->fractal_number == 7))
	{
		f->power++;
		f->fractal_number = 7;
	}
	else if (key == 45 && f->fractal_number == 7)
	{
		if (f->power == 3) // pour deux on revient sur un mandelbrot normal ?
			f->fractal_number = 1;
		else
			f->fractal_number = 7;
		f->power--;
	}
	if (f->debug == 1)
		printf("multibrot power %f\n", f->power);
}

void	backspace_switch(int key, t_fractal *f) // marche pas !
{
	if (key == BACKSPACE)
	{
		double tmp;
		tmp = f->fractal_number;
		f->fractal_number = f->tmp_fractal_number;
		f->tmp_fractal_number = tmp;
		tmp = f->shift_x;
		f->shift_x = f->tmp_shift_x;
		f->tmp_shift_x = tmp;
		tmp = f->shift_y;
		f->shift_y = f->tmp_shift_y;
		f->tmp_shift_y = tmp;
		tmp = f->zoom;
		f->zoom = f->tmp_zoom;
		f->tmp_zoom = tmp;
	}
}

void	julia_moves(int key, t_fractal *f)
{
	if (key == 65431) // pav num 8
		f->j_x += 1 * f->tmp_zoom / 1000;
	else if (key == 65433) // pav num 2
		f->j_x -= 1 * f->tmp_zoom / 1000;
	else if (key == 65430) // pav num 4
		f->j_y += 1 * f->tmp_zoom / 1000;
	else if (key == 65432) // pav num 6
		f->j_y -= 1 * f->tmp_zoom / 1000;
	if (f->debug == 1)
		printf("j_x = %f\nj_y = %f\n", f->j_x, f->j_y);
}

void	set_origin(t_fractal *f)
{
	f->o.x = f->j_x;
	f->o.y = f->j_y;
	if (f->debug == 1)
	{
		printf("o.x = %f\n", f->o.x);
		printf("o.y = %f\n", f->o.y);
	}
	f->origin = 1;
}

void	set_arrival(t_fractal *f)
{
	f->a.x = f->j_x;
	f->a.y = f->j_y;
	if (f->debug == 1)
	{
		printf("a.x = %f\n", f->a.x);
		printf("a.y = %f\n", f->a.y);
	}
	f->origin = 0;
	f->d.x = f->a.x - f->o.x;
	f->d.y = f->a.y - f->o.y;
	f->tmp_shift_x = f->shift_x;
	f->tmp_shift_y = f->shift_y;
	f->tmp_zoom = f->zoom;
	f->tmp_fractal_number = f->fractal_number;
	if (f->fractal_number <= 3)
		f->fractal_number = f->fractal_number + 3;
	else if (f->fractal_number == 7)
		f->fractal_number++;
	travel_between_fractals(f);
}

// 115 = S
// 97 == a
void	julia_constant_selector(int key, t_fractal *f)
{
	if (key == 97 && f->bind_combo == 1)
		f->origin = 0;
	if (key == 97 && f->bind_combo == 0)
	{
		if (f->origin == 0)
			set_origin(f);
		else
			set_arrival(f);
	}
}

void	combo_keys(int key, t_fractal *f)
{
	if (key == SHIFT)
	{
		if (f->bind_combo == 0)
			f->bind_combo = 1;
		else
			f->bind_combo = 0;
	}
	if (key == CTRL_L) // ctrl L ?
	{
		if (f->bind_combo_z == 0)
			f->bind_combo_z = 1;
		else
			f->bind_combo_z = 0;
	}
	if (key == ALT_L) // alt_l // le color shift marche plus ?
	{
		if (f->bind_combo_t == 0)
			f->bind_combo_t = 1;
		else
			f->bind_combo_t = 0;
	}
}

void	psyche_switch(int key, t_fractal *f)
{
	if (key == P) // 112 == p
	{
		if (f->psyche_switch == 0)
			f->psyche_switch = 1;
		else
			f->psyche_switch = 0;
	}
}

void	debug_switch(int key, t_fractal *f)
{
	if (key == D)
	{
		if (f->debug == 0)
			f->debug = 1;
		else if (f->debug == 1)
			f->debug = 0;
	}
}

void	space_pause(int key, t_fractal *f)
{
	if (key == SPACE) // espace
	{
		if (f->traveling == 1)
			f->traveling = 0;
		else
			f->traveling = 1;
		/* f->zooming_in = 0; */
		/* f->zooming_out = 0; */
	}
}

void	animation_speed_keys(int key, t_fractal *f)
{
	if (key == PLUS && f->bind_combo_t == 1)
		f->tc *= 2;
	if (key == MINUS && f->bind_combo_t == 1)
		f->tc /= 2;
}

// on key release
int	shift_toggle(int key, t_fractal *f)
{
	if (key == SHIFT)
		f->bind_combo = 0;
	else if (key == CTRL_L) // ctrl_L
		f->bind_combo_z = 0;
	else if (key == ALT_L) // alt_l
		f->bind_combo_t = 0;
	return (0);
}

// conserver le zoom et le shift de chaque fractale quand on switch
int	kb_inputs(int key, t_fractal *f)
{
	printf("key = %d\n", key);
	if (key == WIN_X || key == ESC)
		quit(f);
	arrows(key, f);
	pav_num_operators(key, f);
	combo_keys(key, f);
	psyche_switch(key, f);
	debug_switch(key, f);
	num_fractal_switch(key, f);
	color_shift(key, f);
	multibrot_power_switch(key, f);
	backspace_switch(key, f);
	julia_moves(key, f);
	julia_constant_selector(key, f);
	animation_speed_keys(key, f);
	space_pause(key, f);
	iterate_on_pixels(f);
	return (0);
}
