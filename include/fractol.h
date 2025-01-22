/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:31:56 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/21 12:31:07 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"

// keyboard inputs
# define ESC 65307
# define PLUS 65451
# define MINUS 65453
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364
# define ENTER 65293 // mettre click souris a la place
# define NUM_ENTER 65421
# define SHIFT 65505
# define SWITCH1 109
# define SWITCH2 106
# define SWITCH3 98
# define SWITCH4 116

// Mouse inputs
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_WHEEL_CLICK 2
# define MOUSE_L 1
# define MOUSE_R 3

// Window datas
# define WINSIZE_X 800
# define WINSIZE_Y 800
# define WIN_X 17

// A virer en fonction de comment on gere les couleurs
# define BLACK 0x000000
# define WHITE 0xFFFFFF
//
# define PURE_GREEN 0x00FF00
# define PURE_BLUE 0x0000FF
// #define COLOR_1 0xFF00FF  // Magenta
// #define COLOR_2 0x00FFFF  // Cyan
// #define COLOR_3 0xFFFF00  // Yellow
// #define COLOR_4 0xFF6347  // Tomato Red
// #define COLOR_5 0x7FFF00  // Chartreuse Green
// #define COLOR_6 0x8A2BE2  // BlueViolet
// #define COLOR_7 0xFF1493  // DeepPink
// #define COLOR_8 0x00FF7F  // SpringGreen
// #define COLOR_9 0xFFD700  // Gold
// #define COLOR_10 0xFF4500 // OrangeRed
// #define COLOR_11 0x32CD32 // LimeGreen
// #define COLOR_12 0x00BFFF // DeepSkyBlue
// #define COLOR_13 0x8B008B // DarkMagenta
// #define COLOR_14 0xFF69B4 // HotPink
// #define COLOR_15 0xD2691E // Chocolate
// #define COLOR_16 0x4B0082 // Indigo

// structures
// mlx-img
typedef struct s_img
{
	void		*img_p;
	char		*pixels;
	int			bpp;
	int			endian;
	int			line_len;
}				t_img;

// complex numbers
typedef struct s_complex
{
	double x; // real
	double y; // imaginary
}				t_complex;

// to divide : mlx win / fractal / pointofview
typedef struct s_fractal
{
	int			fractal_number;
	void		*mlx;
	void		*win;
	t_img		img;
	double		escape_value;
	int			max_iterations;
	int			switch_iterations;
	double		shift_x;
	double		shift_y;
	double		zoom;
	double		tmp_shift_x;
	double		tmp_shift_y;
	double		tmp_zoom;
	double		j_x;
	double		j_y;
	double		mouse_x;
	double		mouse_y;
	t_complex	z;
	t_complex	c;
	double		mu;
	int 			bind_combo;
}				t_fractal;

// functions in files
// a classer ou virer
void			set_mandelbrot(int x, int y, t_fractal *f);
int				quit(t_fractal *f);

// color.c
int				generate_smooth_color(int iteration, double mu,
					int max_iterations);
void			colorize_pixel(int x, int y, t_img *img, int color);
int				generate_smooth_color(int iteration, double mu,
					int max_iterations);

// render_fractal.c
void			calculate_f(t_fractal *f);
void			set_complexes(int x, int y, t_fractal *f);
void			iterate_on_pixels(t_fractal *f);
void			render_fractal(int x, int y, t_fractal *f);
double			scale(double unscaled_num, double new_min, double new_max,
					double old_min, double old_max);

// inputs.c
int				mouse_inputs(int key, int x, int y, t_fractal *f);
int				kb_inputs(int key, t_fractal *f);
int				julia_dynamic(int x, int y, t_fractal *f);
int shift_toggle(int key, t_fractal *f);

// init.c
int				init_win(t_fractal *f);
int				init_fra(t_fractal *f);

// maths.c
double			norm_complex(t_complex z);
t_complex		sum_complex(t_complex z1, t_complex z2);
t_complex		square_complex(t_complex z);

#endif
