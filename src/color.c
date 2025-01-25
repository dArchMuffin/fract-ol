/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:28:27 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/23 18:30:25 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
#include <math.h>

// lire la doc pour ca !
void	colorize_pixel(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp));
	*(unsigned int *)(img->pixels + offset) = color;
}

void	init_palette_R(int palette_R[20])
{
	palette_R[0] = 0xFF0000;
	palette_R[1] = 0xFF4500;
	palette_R[2] = 0xFF6347;
	palette_R[3] = 0xFF7F00;
	palette_R[4] = 0xFFB300;
	palette_R[5] = 0xFFD700;
	palette_R[6] = 0xFFFF00;
	palette_R[7] = 0xEEDD82;
	palette_R[8] = 0xF0E68C;
	palette_R[9] = 0xDAA520;
	palette_R[10] = 0xB8860B;
	palette_R[11] = 0x9ACD32;
	palette_R[12] = 0xADFF2F;
	palette_R[13] = 0x7FFF00;
	palette_R[14] = 0x32CD32;
	palette_R[15] = 0x00FF00;
	palette_R[16] = 0x00FA9A;
	palette_R[17] = 0x20B2AA;
	palette_R[18] = 0x5F9EA0;
	palette_R[19] = 0x4682B4;
}

void	init_palette_B(int palette_B[20])
{
	palette_B[0] = 0x00FF00;
	palette_B[1] = 0x006400;
	palette_B[2] = 0x228B22;
	palette_B[3] = 0x32CD32;
	palette_B[4] = 0x00FF00;
	palette_B[5] = 0x7FFF00;
	palette_B[6] = 0x9ACD32;
	palette_B[7] = 0x6B8E23;
	palette_B[8] = 0x556B2F;
	palette_B[9] = 0x8FBC8F;
	palette_B[10] = 0x2E8B57;
	palette_B[11] = 0x3CB371;
	palette_B[12] = 0x20B2AA;
	palette_B[13] = 0xADFF2F;
	palette_B[14] = 0x7CFC00;
	palette_B[15] = 0x98FB98;
	palette_B[16] = 0x00FA9A;
	palette_B[17] = 0x00FF7F;
	palette_B[18] = 0x00FF00;
	palette_B[19] = 0x66CDAA;
}

void	init_palette_G(int palette_G[20])
{
	palette_G[0] = 0x0000FF;
	palette_G[1] = 0x1E90FF;
	palette_G[2] = 0x6495ED;
	palette_G[3] = 0x4169E1;
	palette_G[4] = 0x00008B;
	palette_G[5] = 0x0000CD;
	palette_G[6] = 0x4682B4;
	palette_G[7] = 0x5F9EA0;
	palette_G[8] = 0xB0C4DE;
	palette_G[9] = 0xADD8E6;
	palette_G[10] = 0x87CEFA;
	palette_G[11] = 0x87CEEB;
	palette_G[12] = 0x4682B4;
	palette_G[13] = 0x5F9EA0;
	palette_G[14] = 0x191970;
	palette_G[15] = 0x8A2BE2;
	palette_G[16] = 0x7B68EE;
	palette_G[17] = 0x6A5ACD;
	palette_G[18] = 0x8B008B;
	palette_G[19] = 0x9932CC;
}

int	*palette_selector(int n)
{
	int	palette_R[20];
	int	palette_G[20];
	int	palette_B[20];
	int	*palettes[3];

	init_palette_R(palette_R);
	init_palette_B(palette_B);
	init_palette_G(palette_B);
	palettes[0] = palette_R;
	palettes[1] = palette_G;
	palettes[2] = palette_B;
	if (n >= 0 && n < 3)
	{
		return (palettes[n]);
	}
	else if (n >= 3)
	{
		return (palettes[n % 3]);
	}
	return (palettes[0]);
}
// HSL ?
/* int	*palette_selector(int n) */
/* { */
/* 	int palette_R[20]; */
/* 	int palette_G[20]; */
/* 	int palette_B[20]; */
/* 	int palettes[3]; */
/**/
/* 	palette_R = {0xFF0000, 0xFF4500, 0xFF6347, 0xFF7F00, 0xFFB300, */
/* 		0xFFD700, 0xFFFF00, 0xEEDD82, 0xF0E68C, 0xDAA520, 0xB8860B, 0x9ACD32, */
/* 		0xADFF2F, 0x7FFF00, 0x32CD32, 0x00FF00, 0x00FA9A, 0x20B2AA, 0x5F9EA0, */
/* 		0x4682B4}; */
/* 	palette_G = {0x0000FF, 0x1E90FF, 0x6495ED, 0x4169E1, 0x00008B, */
/* 		0x0000CD, 0x4682B4, 0x5F9EA0, 0xB0C4DE, 0xADD8E6, 0x87CEFA, 0x87CEEB, */
/* 		0x4682B4, 0x5F9EA0, 0x191970, 0x8A2BE2, 0x7B68EE, 0x6A5ACD, 0x8B008B, */
/* 		0x9932CC}; */
/* 	palette_B = {0x00FF00, 0x006400, 0x228B22, 0x32CD32, 0x00FF00, */
/* 		0x7FFF00, 0x9ACD32, 0x6B8E23, 0x556B2F, 0x8FBC8F, 0x2E8B57, 0x3CB371, */
/* 		0x20B2AA, 0xADFF2F, 0x7CFC00, 0x98FB98, 0x00FA9A, 0x00FF7F, 0x00FF00, */
/* 		0x66CDAA}; */
/* 	palettes[] = {palette_R, palette_G, palette_B}; */
/**/
/* 	if (n >= 0 && n < 3) */
/* 		return (palettes[n]); */
/* 	else if (n >= 3) */
/* 		return (palettes[n % 3]); */
/* 	return (palettes[0]); */
/* } */

// A revoir
int	generate_smooth_color(int iteration, double mu, int max_iterations,
		int color_modify, int palette_n)
{
	double	t;
	int		index;
	int		*palette;
	int		palette_size;

	(void)color_modify;
	palette = palette_selector(palette_n);
	palette_size = 20;
	t = (iteration + mu /* + color_modify */) / max_iterations;
	// Fraction lissée
	index = (int)(t * palette_size) % palette_size;
	return (palette[index]);
}

// david tip :
//
// Les nombres de type double sont codés sur 64 bits dont :

/*     52 bits pour la mantisse */
/*     11 bits pour l'exposant */
/*     1 bit pour le signe */
/* je veux recuperer l'exposant
 * bit shift vers la gauche de 52 bits
 * puis bit shift a droite de 53 bits
 * je transforme en int : me donne le nombre de l'exposant
 *
 * */

/**
 * Interpolation linéaire entre deux couleurs
 */
/* int	interpolate_color(int color1, int color2, double t) */
/* { */
/* 	int	r; */
/* 	int	g; */
/* 	int	b;  0xFF8FBC8F 0x0000FF 000011111 */

/*  pour un integer : decaler une fois a droite == / 2   */

/* 	r = ((1 - t) * ((color1 >> 16) & 0xFF)) + (t * ((color2 >> 16) & 0xFF)); */
/* 	g = ((1 - t) * ((color1 >> 8) & 0xFF)) + (t * ((color2 >> 8) & 0xFF)); */
/* 	b = ((1 - t) * (color1 & 0xFF)) + (t * (color2 & 0xFF)); */
/* 	return ((r << 16) | (g << 8) | b); */
/* } */
/**/
/* int	generate_smooth_color(int iteration, double mu, int max_iterations) */
/* { */
/* 	int	palette_size; */
/* 	int	color1; */
/* 	int	color2; */
/* 	int palette[] = { */
/* 		0xFF0000, // Rouge */
/* 		0xFF7F00, // Orange */
/* 		0xFFFF00  // Jaune */
/* 			0x00FF00, // Vert */
/* 			0x0000FF, // Bleu */
/* 			0x4B0082, // Indigo */
/* 			0x8B00FF  // Violet */
/* 	}; */
/* 	double t = (iteration + 1 - mu) / max_iterations; // Fraction lissée */
/* 	palette_size = sizeof(palette) / sizeof(int); */
/* 	color1 = palette[(int)(t * palette_size) % palette_size]; */
/* 	color2 = palette[((int)(t * palette_size) + 1) % palette_size]; */
/* 	return (interpolate_color(color1, color2, fmod(t * palette_size, 1.0))); */
/* } */
