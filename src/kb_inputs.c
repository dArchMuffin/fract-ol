/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_inputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:53:43 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/26 22:35:39 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
#include <math.h>

int	arrows(int key, t_fractal *f)
{
	if (key == RIGHT)
		f->shift_x += (0.2 * f->zoom);
	else if (key == LEFT)
		f->shift_x -= (0.2 * f->zoom);
	else if (key == DOWN)
	{
		if (f->bind_combo_shift == 1)
			f->zoom *= 0.7;
		else
			f->shift_y -= (0.2 * f->zoom);
	}
	else if (key == UP)
	{
		if (f->bind_combo_shift == 1)
			f->zoom *= 1.3;
		else
			f->shift_y += (0.2 * f->zoom);
	}
	return (key);
}

void	combo_keys(int key, t_fractal *f)
{
	if (key == SHIFT)
	{
		if (f->bind_combo_shift == 0)
			f->bind_combo_shift = 1;
		else if (f->bind_combo_shift == 1)
			f->bind_combo_shift = 0;
	}
	if (key == ALT_L) 
	{
		if (f->bind_combo_alt_l == 0)
			f->bind_combo_alt_l = 1;
		else if (f->bind_combo_alt_l == 1)
			f->bind_combo_alt_l = 0;
	}
	if (key == CTRL_L) 
	{
		if (f->bind_combo_ctrl_l == 0)
			f->bind_combo_ctrl_l = 1;
		else if (f->bind_combo_ctrl_l == 1)
			f->bind_combo_ctrl_l = 0;
	}
}

int	shift_toggle(int key, t_fractal *f)
{
	if (key == SHIFT)
		f->bind_combo_shift = 0;
	else if (key == CTRL_L) 
		f->bind_combo_ctrl_l = 0;
	else if (key == ALT_L)
		f->bind_combo_alt_l = 0;
	return (0);
}

int	kb_inputs(int key, t_fractal *f)
{
	if (key == WIN_X || key == ESC)
		quit(f);
	combo_keys(key, f);
	arrows(key, f);
	pav_num_operators(key, f);
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
