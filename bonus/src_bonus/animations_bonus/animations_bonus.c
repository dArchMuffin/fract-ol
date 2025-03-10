/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:30:09 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/22 10:40:58 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minilibx-linux/mlx.h"
#include "../../include_bonus/fractol_bonus.h"

void	animated_zoom_out(int x, int y, t_data *f)
{
	f->flags.zooming_out = 0;
	if (f->zoom < 1)
	{
		f->flags.zooming_out = 1;
		f->zoom /= (1 - f->speed_factor);
		if (f->zoom > 0.1)
		{
			f->shift_view.x -= (x - (WINSIZE >> 1)) * f->zoom * 0.0001;
			f->shift_view.y += (y - (WINSIZE >> 1)) * f->zoom * 0.0001;
			f->shift_view.x *= 0.99;
			f->shift_view.y *= 0.99;
			if (f->zoom > 0.9)
			{
				f->zoom = 1;
				f->shift_view.x = 0.0;
				f->shift_view.y = 0.0;
			}
		}
	}
	iterate_on_pixels(f);
	mlx_do_sync(f->mlx.mlx);
}

void	animated_zoom_in(t_data *f)
{
	f->flags.zooming_in = 0;
	if (f->zoom > f->zoom * 0.5)
	{
		f->flags.zooming_in = 1;
		f->zoom *= (1 - f->speed_factor);
		iterate_on_pixels(f);
		mlx_do_sync(f->mlx.mlx);
	}
}

void	animated_zoom(int key, int x, int y, t_data *f)
{
	if (key == MOUSE_R && f->flags.bind_combo_alt_l == 0
		&& f->flags.bind_combo_ctrl_l == 1 && f->flags.bind_combo_shift == 0)
		set_animated_zoom_out(x, y, f);
	else if (key == MOUSE_L && f->flags.bind_combo_ctrl_l == 1
		&& f->flags.bind_combo_alt_l == 0 && f->flags.bind_combo_shift == 0)
	{
		if (f->flags.zooming_in == 0)
		{
			f->flags.zooming_out = 0;
			animated_zoom_in(f);
		}
		else
			f->flags.zooming_in = 0;
	}
}

int	update_animations(t_data *f)
{
	if (f->flags.traveling == 1)
		travel_between_fractals(f);
	if (f->flags.zooming_out == 1)
		animated_zoom_out(f->zooming_out_coords.x, f->zooming_out_coords.y, f);
	if (f->flags.zooming_in == 1)
		animated_zoom_in(f);
	if (f->flags.fractal_switch == 1)
		first_render(f);
	return (0);
}
