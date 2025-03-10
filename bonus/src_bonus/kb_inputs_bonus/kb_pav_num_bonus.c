/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb_pav_num_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:03:51 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/22 10:24:23 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/fractol_bonus.h"

int	pav_num_enter(int key, t_data *f)
{
	if (key == NUM_ENTER)
	{
		if (f->flags.bind_combo_shift == 1)
		{
			f->max_iterations = MIN_I;
			f->switch_iterations = MIN_I;
		}
		else
			f->max_iterations = f->switch_iterations;
	}
	return (key);
}

int	pav_num_operators(int key, t_data *f)
{
	if (key == PLUS && f->flags.bind_combo_shift == 0
		&& f->flags.bind_combo_ctrl_l == 0)
		f->switch_iterations += 1;
	else if (key == MINUS && f->switch_iterations > 1
		&& f->flags.bind_combo_shift == 0 && f->flags.bind_combo_ctrl_l == 0)
		f->switch_iterations -= 1;
	pav_num_enter(key, f);
	return (key);
}
