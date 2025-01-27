/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:28:27 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/26 22:41:41 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
#include <math.h>
#include <stdlib.h>

// lire la doc pour ca !
void	colorize_pixel(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp));
	*(unsigned int *)(img->pixels + offset) = color;
}


void init_palette_R(int palette_R[20])
{
    palette_R[0] = 0x000000; // Noir
    palette_R[1] = 0x330000; // Rouge très sombre
    palette_R[2] = 0x663300; // Rouge très sombre, tendant vers l'orange
    palette_R[3] = 0x993300; // Rouge foncé, tendant vers l'orange
    palette_R[4] = 0xCC3300; // Rouge vif foncé, tendant vers l'orange
    palette_R[5] = 0xFF3300; // Rouge pur, tendant vers l'orange
    palette_R[6] = 0xFF6633; // Rouge clair, tendant vers l'orange
    palette_R[7] = 0xFF9966; // Rouge pâle, tendant vers l'orange
    palette_R[8] = 0xFFCC99; // Orange clair
    palette_R[9] = 0xFFCC66; // Pêche clair
    palette_R[10] = 0xFFD966; // Orange pastel
    palette_R[11] = 0xFFE0B3; // Très clair, pêche
    palette_R[12] = 0xFFE6B3; // Très pâle, orange doux
    palette_R[13] = 0xFFB366; // Pêche très clair
    palette_R[14] = 0xFF9966; // Orange très clair
    palette_R[15] = 0xFF4C00; // Rouge/orange vif
    palette_R[16] = 0xCC6600; // Orange moyen
    palette_R[17] = 0x993300; // Rouge intense
    palette_R[18] = 0xFF3300; // Rouge très intense, vers l'orange
    palette_R[19] = 0xFFFFFF; // Blanc
}

void init_palette_B(int palette_B[20])
{
    palette_B[0] = 0x000000; // Noir
    palette_B[1] = 0x000033; // Bleu très sombre
    palette_B[2] = 0x000066; // Bleu profond
    palette_B[3] = 0x000099; // Bleu intense
    palette_B[4] = 0x0000CC; // Bleu vif foncé
    palette_B[5] = 0x0000FF; // Bleu pur
    palette_B[6] = 0x4C4CFF; // Bleu clair
    palette_B[7] = 0x8080FF; // Bleu pâle
    palette_B[8] = 0xA6A6FF; // Bleu très pâle
    palette_B[9] = 0xB3B3FF; // Bleu clair pâle
    palette_B[10] = 0xCCCCFF; // Bleu très clair
    palette_B[11] = 0xD1A6FF; // Violet clair
    palette_B[12] = 0xE0A6FF; // Violet pastel
    palette_B[13] = 0xF2A6FF; // Violet doux
    palette_B[14] = 0xF2B3FF; // Rose clair
    palette_B[15] = 0xF2CCE6; // Rose pâle
    palette_B[16] = 0xF2E0FF; // Rose très pâle
    palette_B[17] = 0xE6E6FF; // Très pâle (un peu de violet)
    palette_B[18] = 0x000099; // Bleu intense
    palette_B[19] = 0xFFFFFF; // Blanc
}


void init_palette_G(int palette_G[20])
{
    palette_G[0] = 0x000000; // Noir
    palette_G[1] = 0x003300; // Vert très sombre
    palette_G[2] = 0x336600; // Vert foncé, tendant vers le jaune
    palette_G[3] = 0x669900; // Vert intense, tendant vers le jaune
    palette_G[4] = 0x99CC00; // Vert vif foncé, tendant vers le jaune
    palette_G[5] = 0xCCFF00; // Vert pur, tendant vers le jaune
    palette_G[6] = 0x99FF33; // Vert clair, tendant vers le jaune
    palette_G[7] = 0xCCFF66; // Vert pâle, tendant vers le jaune
    palette_G[8] = 0xFFFF99; // Jaune très clair, vert clair
    palette_G[9] = 0xFFFF66; // Jaune clair
    palette_G[10] = 0xFFFF33; // Jaune vif
    palette_G[11] = 0xFFCC00; // Jaune pâle
    palette_G[12] = 0xFF9900; // Orange clair, plus proche du jaune
    palette_G[13] = 0xFF6600; // Jaune/orange vif
    palette_G[14] = 0xFF3300; // Jaune intense
    palette_G[15] = 0xFFFF00; // Jaune pur
    palette_G[16] = 0xFFFF33; // Très clair, jaune léger
    palette_G[17] = 0xCCFF00; // Jaune-vert vif
    palette_G[18] = 0x99CC00; // Vert vif, tendant vers le jaune
    palette_G[19] = 0xFFFFFF; // Blanc
}

void palette_init(t_palette *palette)
{
    int i;

    i = 0;
	init_palette_R(palette->palette_R);
	init_palette_B(palette->palette_B);
	init_palette_G(palette->palette_G);

    while (i < 20)
    {
        palette->palettes[0][i] = palette->palette_R[i];
        i++;
    }
    i = 0;
    while (i < 20)
    {
        palette->palettes[1][i] = palette->palette_G[i];
        i++;
    }
    i = 0;
    while (i < 20)
    {
        palette->palettes[2][i] = palette->palette_B[i];
        i++;
    }
    
	/* palette->palettes[0] = palette->palette_R; */
	/* palette->palettes[1] = palette->palette_G; */
	/* palette->palettes[2] = palette->palette_B; */
	/* if (palette->n >= 0 && palette->n < 3) */
	/*     return (palette->palettes[palette->n]); */
	/* else  */
	/*     return (palette->palettes[0]); */
}

// HSL ?
// A revoir
int	generate_smooth_color(int iteration, double mu, int max_iterations, t_palette *palette)
{
	double	t;
	int		index;

    if (palette == NULL) 
        return (0); 
    t = (iteration + mu) / max_iterations;
	if (t < 0) t = 0;
    if (t > 1) t = 1;
	index = (int)(t * PALETTE_SIZE) % PALETTE_SIZE;
    if (index < 0) index = 0;
    if (index >= PALETTE_SIZE) index = PALETTE_SIZE - 1;

    return (palette->palettes[palette->n][index]);
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
/* 	int	PALETTE_SIZE; */
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
/* 	PALETTE_SIZE = sizeof(palette) / sizeof(int); */
/* 	color1 = palette[(int)(t * PALETTE_SIZE) % PALETTE_SIZE]; */
/* 	color2 = palette[((int)(t * PALETTE_SIZE) + 1) % PALETTE_SIZE]; */
/* 	return (interpolate_color(color1, color2, fmod(t * PALETTE_SIZE, 1.0))); */
/* } */
