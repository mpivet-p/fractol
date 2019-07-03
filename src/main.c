/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/04 00:56:50 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fill_pxl(char *image, int x, int y, int color)
{
	int i;

	i = (((SIMG_X * y) + x) * 4);
	if (x > 0 && y > 0 && x < SIMG_X && y < SIMG_Y)
	{
		image[i + 2] = (color >> 16) & 0xFF;
		image[i + 1] = (color >> 8) & 0xFF;
		image[i + 0] = color & 0xFF;
	}
}

void	init_mandelbrot(t_fmlx *mlx)
{
	mlx->max_inter = 50;
	mlx->xa = -2.1;
	mlx->xb = 0.6;
	mlx->ya = -1.2;
	mlx->yb = 1.2;
	mlx->fract = 'm';
}

void	init_julia(t_fmlx *mlx)
{
	mlx->max_inter = 50;
	mlx->xa = -1;
	mlx->xb = 1;
	mlx->ya = -1.2;
	mlx->yb = 1.2;
	mlx->fract = 'j';
}

void	mandelbrot(t_fmlx *mlx, t_point coords, t_point zoom)
{
	t_cplx c;
	t_cplx z;
	int i;
	double tmp;

	c.rl = coords.x / zoom.x + mlx->xa;
	c.im = coords.y / zoom.y + mlx->ya;
	z.rl = 0;
	z.im = 0;
	tmp = 0;
	i = 0;
	while (((z.rl * z.rl) + (z.im * z.im)) < 4 && i < mlx->max_inter)
	{
		tmp = z.rl;
		z.rl = (z.rl * z.rl) - (z.im * z.im) + c.rl;
		z.im = 2 * z.im * tmp + c.im;
		i++;
	}
	if (i == mlx->max_inter)
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), 0);
	else
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), 0xFFFFFF);
}

void	julia(t_fmlx *mlx, t_point coords, t_point zoom)
{
	t_cplx c;
	t_cplx z;
	int i;
	double tmp;

	c.rl = 0.285;
	c.im = 0.01;
	z.rl = coords.x / zoom.x + mlx->xa;
	z.im = coords.y / zoom.y + mlx->ya;
	tmp = 0;
	i = 0;
	while (((z.rl * z.rl) + (z.im * z.im)) < 4 && i < mlx->max_inter)
	{
		tmp = z.rl;
		z.rl = (z.rl * z.rl) - (z.im * z.im) + c.rl;
		z.im = 2 * z.im * tmp + c.im;
		i++;
	}
	if (i == mlx->max_inter)
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), 0);
	else
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), 0xFFFFFF);
}

void	disp_fractol(t_fmlx *mlx)
{
	t_point coords;
	t_point zoom;

	coords.x = 0;
	coords.y = 0;
	zoom.x = SIMG_X / (mlx->xb - mlx->xa);
	zoom.y = SIMG_Y / (mlx->yb - mlx->ya);
	ft_bzero(mlx->screen, (SIMG_X * SIMG_Y) * 4);
	while (coords.x < SIMG_X)
	{
		while (coords.y < SIMG_Y)
		{
			if (mlx->fract == 'm')
				mandelbrot(mlx, coords, zoom);
			if (mlx->fract == 'j')
				julia(mlx, coords, zoom);
			coords.y++;
		}
		coords.y = 0;
		coords.x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	fractol_exit(t_fmlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int		deal_key(int key, t_fmlx *mlx)
{
	printf("key = %i\n", key);
	if (key == 35)
		mlx->max_inter += 2;
	else if  (key == 37 && mlx->max_inter > 1)
		mlx->max_inter -= 2;
	else if (key == 53)
		fractol_exit(mlx);
	else if (key == 49)
		init_mandelbrot(mlx);
	disp_fractol(mlx);
	return (key);
}


void	zoom_down(t_fmlx *mlx)
{
	mlx->max_inter += 1;
	mlx->xa *= 0.9;
	mlx->xb *= 0.9;
	mlx->ya *= 0.9;
	mlx->yb *= 0.9;
	disp_fractol(mlx);
}

void	zoom_up(t_fmlx *mlx)
{
	mlx->max_inter += 1;
	mlx->xa *= 1.1;
	mlx->xb *= 1.1;
	mlx->ya *= 1.1;
	mlx->yb *= 1.1;
	disp_fractol(mlx);
}

int		test_mouse(int button, int x, int y, t_fmlx *mlx)
{
	(void)mlx;
	(void)x;
	(void)y;
	if (button == 5)
		zoom_up(mlx);
	if (button == 4)
		zoom_down(mlx);
	return (button);
}

void	fractol(char *name)
{
	t_fmlx	ptr;
	int		bpp;
	int		size_line;
	int		endian;

	if (!(ptr.mlx = mlx_init()))
		fractol_exit(&ptr);
	if (!(ptr.win = mlx_new_window(ptr.mlx, SWIN_X, SWIN_Y, "fractol - ")))
		fractol_exit(&ptr);
	if (!(ptr.img = mlx_new_image(ptr.mlx, SIMG_X, SIMG_Y)))
		fractol_exit(&ptr);
	if (!(ptr.screen = mlx_get_data_addr(ptr.img, &bpp, &size_line, &endian)))
		fractol_exit(&ptr);
	mlx_hook(ptr.win, 2, 0, deal_key, &ptr);
	mlx_hook(ptr.win, 4, 0, test_mouse, &ptr);
	if (name && ft_strcmp(name, "mandel") == 0)
		init_mandelbrot(&ptr);
	else if (name && ft_strcmp(name, "julia") == 0)
		init_julia(&ptr);
//	else if (name && ft_strcmp(name, "mandelbrot") == 0)
//		init_truc(&ptr);
	else
		return ;
	disp_fractol(&ptr);
	mlx_loop(ptr.mlx);
}

int		main(int argc, char **argv)
{
	if (argc != 2 || (ft_strcmp(argv[1], "mandel") != 0
					&& ft_strcmp(argv[1], "julia") != 0
					&& ft_strcmp(argv[1], "koch") != 0))
	{
		ft_putstr_fd("usage : fractol < mandel | julia | koch >\n", 2);
		return (1);
	}
	fractol(argv[1]);
	return (0);
}
