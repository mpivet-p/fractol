/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/02 01:57:16 by mpivet-p         ###   ########.fr       */
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
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), (i * 255 / MAX_INTERACT));
}

void	disp_fractol(t_fmlx *mlx)
{
	t_point coords;
	t_point zoom;

	coords.x = 0;
	coords.y = 0;
	zoom.x = SIMG_X / (mlx->xb - mlx->xa);
	zoom.y = SIMG_Y / (mlx->yb - mlx->ya);
	while (coords.x < SIMG_X)
	{
		while (coords.y < SIMG_Y)
		{
			mandelbrot(mlx, coords, zoom);
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
	if (key == 35)
		mlx->max_inter += 2;
	else if  (key == 37 && mlx->max_inter > 1)
		mlx->max_inter -= 2;
	else if (key == 125)
	{
		mlx->xa += 0.1;
		mlx->ya -= 0.1;
	}
	else if (key == 53)
		fractol_exit(mlx);
	disp_fractol(mlx);
	return (key);
}

void	fractol(void)
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
	ptr.max_inter = 40;
	ptr.xa = FRACT_XA;
	ptr.xb = FRACT_XB;
	ptr.ya = FRACT_YA;
	ptr.yb = FRACT_YB;
	disp_fractol(&ptr);
	mlx_loop(ptr.mlx);
}

int		main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		ft_putstr_fd("usage : fractol < mandel | julia | koch >\n", 2);
		return (1);
	}
	fractol();
	return (0);
}
