/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:18:49 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/18 17:11:29 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
 * Mandelbrot : z0 = 0
 * 							zn+1 = zn^2 + c
 *
 * 							z = resultat de l'addition d'un r et d'un i
 * 							c = i
 * 							chaque iteration : z = z^2 + c
 *
 * Julia : meme formule mais c n'est pas un imaginaire
 * 				c est choisi comme un point specifique du plan complexe
 * 				=> c'est une famille de fractales qui depend du parametre c : position du curseur ? 
 * 				https://mandelbrotandco.com/en.hub169.html?set=Julia
 *
 * 				Dépendance de l'ensemble de Julia sur c : L'ensemble de Julia dépend de la valeur de cc, 
 * 				tout comme l'ensemble de Mandelbrot, mais il se comporte différemment selon que cc appartient 
 * 				ou non à l'ensemble de Mandelbrot.
 * 				
 * 				Caractère dynamique de l'ensemble de Julia : Si cc appartient à l'ensemble de Mandelbrot 
 * 				(c'est-à-dire que la suite zn=zn−12+czn​=zn−12​+c ne diverge pas quand z0=0z0​=0), 
 * 				alors l'ensemble de Julia associé à cette valeur de cc est connecté et forme une structure "solide" sans trous. 
 * 				Si cc ne fait pas partie de l'ensemble de Mandelbrot, l'ensemble de Julia associé à cette valeur est découpé, 
 * 				constitué de plusieurs composants disjoints.
 *
 * 				en gros : Julia applique la formule de mandelbrot MAIS avec z0 pas forcement = 0 mais n'importe quelle valeur c
 *
 * Burning ship : zn+1 = abs(zn^2) + c avec z0 = 0
 * https://math.stackexchange.com/questions/2322660/what-are-3d-burning-ship-fractals
 * https://robotmoon.com/burning-ship-fractal/
 *
 * Newton : zn+1 = zn - (f(zn) / f`(zn)) / f(z) est un polynome generalement f(z) = z^3 - 1
 * */

/*
 * General formula to square a complex number
 *
 * (x_real + y_imaginary)^2
 *
 * (x + yi) * (x + yi)
 *
 * x^2 + xyi + xyi + y^2*i^2     / i^2 = -1 /
 * x^2 + 2xyi - y^2
 * (x^2 - y^2) + (2xyi)
 *  reel(x axis) 	imaginary(y axis)
 *
 * */

//calcul du complex * scale * zoom

/* to do 
 *
 * Makefile relink sur le .h 
 * Ac Av
 * Julia 
 * degrade plus smooth
 * ranger et renommer fonctions
 * regrouper et optimiser
 * checker la doc
 * 			- hooks
 * 			- couleurs
 * revoir le main et l'enchainement des fonctions 
 * */

#include "../include/fractol.h"
#include <X11/X.h> //checker la doc
#include <stddef.h> //stdlib utilise stddef : plus direct
#include <stdio.h> //perror 
#include "../minilibx-linux/mlx.h" 
#include <errno.h>
#include <stdlib.h>

int init_win(t_fractal *f)
{
	f->mlx = mlx_init();
	if (f->mlx == NULL)
		return (-1);
	f->win = mlx_new_window(f->mlx, WINSIZE, WINSIZE, "Fractol"); //changer selon l'input le nom de la fenetre
	f->img.img_p = mlx_new_image(f->mlx, WINSIZE, WINSIZE);
	f->img.pixels=mlx_get_data_addr(f->img.img_p, &f->img.bpp, &f->img.line_len, &f->img.endian);
	f->escape_value = 4; // pour mandelbrot : hypothenus et pythagore
	f->max_iterations = 200;
	f->img.bpp /= 8; //conseil pour afficher 4 pixels d'un coup ?
	/* f->shift_x = 0.0; */
	/* f->shift_y = 0.0; */
	/* f->zoom = 1.0; */
	return (0);
}

int quit(t_fractal *f)
{
	if (!f)
		exit(1);
	if (f->img.img_p)
		mlx_destroy_image(f->mlx, f->img.img_p);
	if (f->win)
		mlx_destroy_window(f->mlx, f->win);
	if (f->mlx)
	{
		mlx_loop_end(f->mlx); //je capte pas cette fonction
		mlx_destroy_display(f->mlx);
		free(f->mlx);
	}
	exit(0); //checker la dif entre exit 1 et exit 0
}

int inputs(int key, t_fractal *f)
{
	if (key == WIN_X || key == ESC)
		quit(f);
	return (0);
}

double scale(double unscaled_num, double new_min, double new_max, double old_min, double old_max) //a reecrire
{
	return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min;
}

void colorize_pixel(int x, int y, t_img *img, int color) //degrader a gerer ici ?
//je capte pas ce que je fais la 
{
	int offset;

	offset = (y * img->line_len) + (x * (img->bpp));
	*(unsigned int *)(img->pixels + offset) = color;
}

t_complex 	sum_complex(t_complex z1, t_complex z2)
{
	t_complex result;

	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result); 
}

t_complex 	square_complex(t_complex z)
{
	t_complex 	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}

void 	mandelbrot_f(int x, int y, t_fractal *f)
{
	t_complex z;
	t_complex c;
	int 		i;
	int 		color;

	i = 0;

	//parce que z0 = 0 ET que z est reel et n'est pas dans le plan complexe  
	z.x = 0.0;
	z.y = 0.0;

	//parce que z = a + bi // z = x + yi // on veut savoir ou se situe c sur le plan complex ?
	c.x = scale(x, -3, +3, 0, WINSIZE); //* f->zoom) + f->shift_x;
	c.y = scale(y, +3, -3, 0, WINSIZE); // * f->zoom) + f->shift_y;

	while (i < f->max_iterations)
	{
		// z = result of addition of a real (r) and an imaginary (c) number
		// c = imaginary number
		z = sum_complex(square_complex(z), c);

				//value escaped ? hypothenus > 2
		// Here we can't compute to infinity but it's safe to say that if the
    /* absolute value of Z goes above 2, it will tend toward infinity and */
    /* the number won't be part of the Mandelbrot set. */
				if ((z.x * z.x) + (z.y * z.y) > f->escape_value)
				{
					color = scale(i, PURE_BLUE, PURE_GREEN, 0, f->max_iterations);
					colorize_pixel(x, y, &f->img, color);
					return ;
				}
				++i;
		colorize_pixel(x, y, &f->img, BLACK);
	}
}

void 	iterate_on_pixels(t_fractal *f)
{
	int x;
	int y;

	y = 0;
	while (y < WINSIZE)
	{
		x = 0;
		while (x < WINSIZE)
		{
			mandelbrot_f(x, y, f);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img_p, 0, 0);
}

int main(void)
{
	t_fractal f;

	init_win(&f);
	iterate_on_pixels(&f);
	mlx_hook(f.win, WIN_X, 0, quit, &f); // Comment la mixer avec inputs ?
	mlx_hook(f.win, KeyPress, KeyPressMask, inputs, &f);
	/* mlx_hook(f.win, KeyPress, KeyPressMask, quit, &f); */

	mlx_loop(f.mlx);
	
	return (0);
}




//faire un scale pour les couleurs plutot que reprendre scale
/* double scale(double unscaled_num, double new_min, double new_max, double old_min, double old_max) //a reecrire */
/* { */
/* 	return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min; */
/* } */
/**/
/* void colorize_pixel(int x, int y, t_img *img, int color) //degrader a gerer ici ? */
/* //je capte pas ce que je fais la  */
/* { */
/* 	int offset; */
/**/
/* 	offset = (y * img->line_len) + (x * (img->bpp)); */
/* 	*(unsigned int *)(img->pixels + offset) = color; */
/* } */
/**/
/* void 	iterate_on_pixels(t_fractal *f) */
/* { */
/* 	int x; */
/* 	int y; */
/**/
/* 	y = 0; */
/* 	while (y < WINSIZE) */
/* 	{ */
/* 		x = 0; */
/* 		while (x < WINSIZE) */
/* 		{ */
/* 			mandelbrot_f(x, y, f); */
/* 			x++; */
/* 		} */
/* 		y++; */
/* 	} */
/* 	mlx_put_image_to_window(f->mlx, f->win, f->img.img_p, 0, 0); */
/* } */
/**/
/**/
/* int	main(void) */
/* { */
/* 	t_fractal	f; */
/**/
/* 	init(&f); */
/* 	iterate_on_pixels(&f);  */
/* 	mlx_hook(f.win, WIN_X, 0, quit_and_free, &f); //a mixer avec inputs  */
/* 	mlx_hook(f.win, KeyRelease, KeyReleaseMask, iterations_inputs, &f); */
/* 	mlx_hook(f.win, KeyPress, KeyPressMask, move_inputs, &f); */
/* 	mlx_hook(f.win, KeyPress, KeyPressMask, quit_inputs, &f); // mixer ces deux qui sont les memes ? */
/* 	mlx_hook(f.win, ButtonRelease, ButtonReleaseMask, zoom_inputs, &f); */
/* 	mlx_hook(f.win, DestroyNotifyMask, StructureNotifyMask, close_handle, f); */ 
/* 	Comment fermer la fenetre avec la croix sans utiliser mlx_hook ? */ 
/* 	mlx_key_hook(f.win, inputs, &f); */ 
/* 	mlx_mouse_hook(fra.win, mouse_wheel_events, &fra); */ 
/* 	mlx_loop(f.mlx); */
/* 	17 = fermer avec la croix */ 
/* 	x mask == filtre permet de programmer un racourci plus complique */ 
/* 	return (0); */
/* } */
