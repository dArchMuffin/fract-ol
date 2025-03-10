/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_fractal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:15 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/28 14:17:11 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/fractol_bonus.h"
#include <math.h>

void	burning_ship(t_data *f)
{
	double	tmp;

	f->z.x = fabsl(f->z.x);
	f->z.y = fabsl(f->z.y);
	tmp = 2 * f->z.x * f->z.y + f->c.y;
	f->z.x = f->z.x * f->z.x - f->z.y * f->z.y + f->c.x;
	f->z.y = tmp;
}

void	tricorn(t_data *f)
{
	double	tmp;

	tmp = -2 * f->z.x * f->z.y + f->c.y;
	f->z.x = f->z.x * f->z.x - f->z.y * f->z.y + f->c.x;
	f->z.y = tmp;
}

void	multibrot(t_data *f)
{
	double	tmp;
	double	n;

	n = f->power;
	tmp = pow(f->z.x * f->z.x + f->z.y * f->z.y, (n - 1) / 2.0) * cos(n
			* atan2(f->z.y, f->z.x)) + f->c.x;
	f->z.y = pow(f->z.x * f->z.x + f->z.y * f->z.y, (n - 1) / 2.0) * sin(n
			* atan2(f->z.y, f->z.x)) + f->c.y;
	f->z.x = tmp;
}

void	calculate_f(t_data *f)
{
	if (f->fractal_number == 1 || f->fractal_number == 4)
		f->z = sum_complex(square_complex(f->z), f->c);
	if (f->fractal_number == 2 || f->fractal_number == 5)
		burning_ship(f);
	if (f->fractal_number == 3 || f->fractal_number == 6)
		tricorn(f);
	if (f->fractal_number == 7 || f->fractal_number == 8)
		multibrot(f);
}
