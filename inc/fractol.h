/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 01:32:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/06 02:31:50 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
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
	FRACT_MANDEL, FRACT_JULIA, FRACT_NUM
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
	double			xmax;
	double			ymin;
	double			ymax;
	double			zoom;
	void			*mlx;
	void			*win;
	void			*img;
	char			*screen;
	int				fract;
	int				max_inter;
}				t_fmlx;

void	zoom_up(t_fmlx *mlx, int x, int y);
void	zoom_down(t_fmlx *mlx, int x, int y);
void	disp_fractol(t_fmlx *mlx);
void	julia(t_fmlx *mlx, t_point coords);
void	init_julia(t_fmlx *mlx);
void	mandelbrot(t_fmlx *mlx, t_point coords);
void	init_mandelbrot(t_fmlx *mlx);
void	fill_pxl(char *image, int x, int y, int color);
int		deal_key(int key, t_fmlx *mlx);
int		test_mouse(int button, int x, int y, t_fmlx *mlx);
void	fractol_exit(t_fmlx *mlx);

#endif
