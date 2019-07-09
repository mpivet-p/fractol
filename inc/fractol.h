/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 01:32:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/09 01:52:35 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define SWIN_X 1000
# define SWIN_Y 800
# define SIMG_X 1000
# define SIMG_Y 800

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

typedef enum	e_fractals
{
	FRACT_MANDEL, FRACT_JULIA, FRACT_BURNING, FRACT_NUM
}				t_fractals;

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

typedef struct	s_cplx
{
	double rl;
	double im;
}				t_cplx;

typedef struct	s_fmlx
{
	double			xmin;
	double			ymin;
	double			zoom;
	struct s_cplx	julia;
	void			*mlx;
	void			*win;
	void			*img;
	char			*screen;
	int				colors;
	int				hide_ui;
	int				fract;
	int				max_inter;
	int				julia_edit;
}				t_fmlx;

/*
**	================ /( )\ ================
**	                FRACTALS
**	================ \( )/ ================
*/

void			julia(t_fmlx *mlx, t_point coords);
void			mandelbrot(t_fmlx *mlx, t_point coords);
void			burningship(t_fmlx *mlx, t_point coords);
void			init_burningship(t_fmlx *mlx);
void			init_julia(t_fmlx *mlx);
void			init_mandelbrot(t_fmlx *mlx);

/*
**	================ /( )\ ================
**	                EVENTS
**	================ \( )/ ================
*/

int				deal_key(int key, t_fmlx *mlx);
int				mouse_roll(int button, int x, int y, t_fmlx *mlx);
int				mouse_move(int x, int y, t_fmlx *mlx);
void			julia_edit(t_fmlx *mlx, int x, int y);
void			zoom_up(t_fmlx *mlx, int x, int y);
void			zoom_down(t_fmlx *mlx, int x, int y);

/*
**	================ /( )\ ================
**	                 TOOLS
**	================ \( )/ ================
*/

void			fractol_exit(t_fmlx *mlx);
int				get_color(t_fmlx *mlx, int i);
void			fill_pxl(char *image, int x, int y, int color);
void			disp_fractol(t_fmlx *mlx);
void			print_ui(t_fmlx *mlx);

#endif
