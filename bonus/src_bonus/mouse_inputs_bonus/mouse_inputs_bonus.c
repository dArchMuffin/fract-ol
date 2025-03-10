/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_inputs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:39:54 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/22 10:52:09 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/include/libft.h"
#include "../../include_bonus/fractol_bonus.h"

void	wheel(int key, int x, int y, t_data *f)
{
	wheel_combo(key, f);
	wheel_zoom(key, x, y, f);
	if (key == MOUSE_WHEEL_CLICK && f->flags.bind_combo_shift == 0
		&& f->flags.bind_combo_ctrl_l == 0 && f->flags.bind_combo_alt_l == 0)
	{
		f->zoom = 1.0;
		f->shift_view.x = 0.0;
		f->shift_view.y = 0.0;
		f->flags.zooming_in = 0;
		f->flags.zooming_out = 0;
		f->max_iterations = MIN_I;
	}
	else if (key == MOUSE_WHEEL_CLICK && f->flags.bind_combo_shift == 1
		&& f->flags.bind_combo_alt_l == 0 && f->flags.bind_combo_ctrl_l == 0)
	{
		if (f->flags.origin == 0)
			wheel_set_origin(f);
		else
			wheel_set_arrival(f);
	}
	else if (key == MOUSE_WHEEL_CLICK && f->flags.bind_combo_shift == 0
		&& f->flags.bind_combo_alt_l == 0 && f->flags.bind_combo_ctrl_l == 1)
		f->max_iterations = MIN_I;
}

void	clicks_combo(int key, t_data *f)
{
	if (key == MOUSE_L && f->flags.bind_combo_shift == 1
		&& f->flags.bind_combo_alt_l == 0 && f->flags.bind_combo_ctrl_l == 0)
	{
		if (f->fractal_number < 4 || f->fractal_number == 7)
		{
			f->tmp.shift_x = f->shift_view.x;
			f->tmp.shift_y = f->shift_view.y;
			f->tmp.zoom = f->zoom;
			f->tmp.fractal_number = f->fractal_number;
			f->shift_view.x = 0.0;
			f->shift_view.y = 0.0;
			f->zoom = 1.0;
			if (f->fractal_number == 7)
				f->fractal_number++;
			else if (f->fractal_number > 0 && f->fractal_number < 4)
				f->fractal_number += 3;
		}
		f->julia_constant.x = f->mouse.x;
		f->julia_constant.y = f->mouse.y;
	}
	switch_palette(key, f);
}

void	clicks(int key, int x, int y, t_data *f)
{
	clicks_combo(key, f);
	if (key == MOUSE_R && f->flags.bind_combo_shift == 0
		&& f->flags.bind_combo_alt_l == 0 && f->flags.bind_combo_ctrl_l == 0)
	{
		f->zoom *= 1.2;
		f->shift_view.x -= (x - (WINSIZE >> 1)) * f->zoom * 0.01;
		f->shift_view.y += (y - (WINSIZE >> 1)) * f->zoom * 0.01;
	}
	else if (key == MOUSE_L && f->flags.bind_combo_shift == 0
		&& f->flags.bind_combo_alt_l == 0 && f->flags.bind_combo_ctrl_l == 0)
	{
		f->zoom *= 0.8;
		f->shift_view.x += (x - (WINSIZE >> 1)) * f->zoom * 0.01;
		f->shift_view.y -= (y - (WINSIZE >> 1)) * f->zoom * 0.01;
	}
}

int	mouse_inputs(int key, int x, int y, t_data *f)
{
	wheel(key, x, y, f);
	clicks(key, x, y, f);
	animated_zoom(key, x, y, f);
	iterate_on_pixels(f);
	return (key);
}
