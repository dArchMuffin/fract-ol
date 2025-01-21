/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:18:49 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/21 12:21:28 by oelleaum         ###   ########lyon.fr   */
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
 *
 * 1 : Julia
 * 	- atobl
 * 	- un seul param ?
 *
 * 2 : gestion d'erreurs
 * 		perror ?
 *
 * 3 : couleurs 
 * 	- trier et choisir les fct
 * 	- faire des sets de couleurs
 *
 * 4 : fcts : 
 * 	- switch colors
 * 	- switch fractal
 *
 * 5 : ranger et subdiviser
 * 	- atodbl
 * 	- init
 * 	- inputs
 * 	- render_fractal
 * 		- racourcir set complexes
 * 		- diviser si 6 fonctions
 * 		- on garde tricorn ?
 * 		- CHANGER ZX POUR ZR ETC
 * 		- essayer d'optimiser les appels aux structs
 * 	- main 
 * 	 	- ranger quit
 * 	 	- revoir l'enchainement
 *
 * 6 : incorporer libft
 * 	- strncmp 
 * 	- printf
 * 	- double atoi pour atdbl
 *
 * 7 : checker la doc
 * 			- hooks
 * 			- couleurs
 * 
 * 8 : Makefile bonus
 * 	- split bonus
 * 	- clean base
 *
 * */

#include "../include/fractol.h"
#include <X11/X.h> //checker la doc
#include <stddef.h> //stdlib utilise stddef : plus direct
#include <stdio.h> //perror 
#include "../minilibx-linux/mlx.h" 
#include <errno.h>
#include <stdlib.h>


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

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


int skip_spaces(char *s, int *sign, int *max_digits)
{
	int i;

	i = 0;
	while (s[i] <= 32 || s[i] == '+') //on avance tant qu'on n'a pas de digit ou de -
		i++;
	if (s[i] == '-') //on prend le moins si jamais
	{
		if (*sign == 1)
			*sign = -1;
		else 
			(*max_digits = -1);
		i++;
	}
	printf("i = %d\n", i);
	return (i);
}

//cas du double . ou du rien avant le . pas gere
double atodbl(char *s, int *max_digits)
{
	int i;
	int dot;
	double res1;
	double res2;
	double factor;
	int sign;

	sign = 1;
	factor = 1.0;
	res1 = 0;
	res2 = 0;
	dot = 0;
	i = 0;
	while (s[i])
	{
		i += skip_spaces(s, &sign, max_digits);
		if (s[i] < '0' && s[i] > '9' && s[i] != '.' && s[i] != '+' && s[i] != '-') //n'importe quel autre char donne une erreur
			*max_digits = -1;
		if (s[i] == '.')
		{
			if (dot > 0)
				*max_digits = -1;
			else 
				dot++;
		}
		i++;
	}
	if (*max_digits >= 0)
	{
		i = 0;
		while (s[i] <= 32 || s[i] == '+' || s[i] == '-')
			i++;
		while (s[i] >= '0' && s[i] <= '9' && (*max_digits)-- > 0)
		{
			res1 = res1 * 10 + s[i] - '0';
			i++;
		}
		if (s[i] == '.')
		{
			i++;
			while (s[i] >= '0' && s[i] <= '9' && (*max_digits)-- > 0)
			{
				res2 = res2 * 10 + s[i] - '0';
				factor *= 10;
				i++;
			}
		}
		res1 = (res1 + res2 / factor) * sign;
		return (res1);
	}
	return (0.0);
}

int main(int ac, char **av)
{
	t_fractal f;
	int check_double;
	double res;

	/* printf("av[1] = %s | cmp = %d\n", av[1], ft_strcmp(av[1], "julia")); */
	res = 0;
	check_double = 15;
	res = atodbl(av[1], &check_double);
	printf("%.14f | checkdouble = %d", res, check_double);
	if (res > 3 || res < 3)
	init_fra(&f);
	if (ac == 2)
	{
		if (ft_strcmp(av[1], "mandelbrot") == 0)
		{
	 		 /* init_mandelbrot(&f);  */
			f.fractal_number = 1;
			printf("mandelbrot_f\n");
		}
		else if (ft_strcmp(av[1], "burning_ship") == 0)
		{
			f.fractal_number = 3;
			printf("burning_ship\n");
		}	
		else if (ft_strcmp(av[1], "tricorn") == 0)
		{
			f.fractal_number = 4;
			printf("tricorn\n");
		}
		else if (ft_strcmp(av[1], "julia") == 0)
		{
			f.fractal_number = 2;
			printf("julia\n");
		}
	}

	/* else if (ac == 2 && ft_strcmp(av[1], "julia") == 0) */
	/* { */
	/* 	//difference entre julia avec et sans param ? */
	/* 	f.fractal_number = 2; */
	/* 	f.j_x = atodbl(av[2]); //todo */
	/* 	f.j_y = atodbl(av[3]); //todo */
	/* 	printf("julia\n"); */
	/* } */
	/**/
	else // a revoir 
	{
		printf("ERROR : type 'mandelbrot, burning_ship, tricorn or julia with or without c.r and c.i\n");
	}
	init_win(&f);
	iterate_on_pixels(&f);
	mlx_hook(f.win, WIN_X, 0, quit, &f); // Comment la mixer avec inputs ?
	mlx_hook(f.win, KeyPress, KeyPressMask, kb_inputs, &f); //peut marcher sans le 3eme param ?
	mlx_hook(f.win, KeyRelease, KeyReleaseMask, shift_toggle, &f);
	mlx_mouse_hook(f.win, mouse_inputs, &f);
	mlx_hook(f.win, MotionNotify, PointerMotionMask, julia_dynamic, &f);
	mlx_hook(f.win, ButtonRelease, ButtonReleaseMask, mouse_inputs, &f);

	mlx_loop(f.mlx);
	
	return (0);
}

