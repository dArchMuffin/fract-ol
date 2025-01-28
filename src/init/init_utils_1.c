/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:01:17 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/28 14:01:19 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	init_index(t_fractal *f)
{
	f->fractal_number = 0;
	f->palette.n = 0;
}

void	init_switch(t_fractal *f)
{
	f->switch_iterations = 20;
	f->power = 2;
}

void	init_limits(t_fractal *f)
{
	f->escape_value = 4;
	f->max_iterations = MIN_I;
}

void	init_coords(t_fractal *f)
{
	f->j_x = 0;
	f->j_y = 0;
	f->mouse_x = 0;
	f->mouse_y = 0;
	f->z.x = 0;
	f->z.y = 0;
	f->c.x = 0;
	f->c.y = 0;
	f->o.x = 0;
	f->o.y = 0;
	f->a.x = 0;
	f->a.y = 0;
	f->d.x = 0;
	f->d.y = 0;
}

void	init_anims(t_fractal *f)
{
	init_coords(f);
	f->t = 0;
	f->tc = 0.01;
	f->mu = 0;
}
