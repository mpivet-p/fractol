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

	c.rl = coords.x / zoom.x + FRACT_XA;
	c.im = coords.y / zoom.y + FRACT_YA;
	z.rl = 0;
	z.im = 0;
	tmp = 0;
	i = 0;
	while (((z.rl * z.rl) + (z.im * z.im)) < 4 && i < MAX_INTERACT)
	{
		tmp = z.rl;
		z.rl = (z.rl * z.rl) - (z.im * z.im) + c.rl;
		z.im = 2 * z.im * tmp + c.im;
		i++;
	}
	if (i == MAX_INTERACT)
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), 0xFFFFFF);
	else
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), i * (0xFFFFFF / MAX_INTERACT));
}

void	disp_fractol(t_fmlx *mlx)
{
	t_point coords;
	t_point zoom;

	coords.x = 0;
	coords.y = 0;
	zoom.x = SIMG_X / (FRACT_XB - FRACT_XA);
	zoom.y = SIMG_Y / (FRACT_YB - FRACT_YA);
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

void	fdf_exit(t_fmlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int		deal_key(int key, t_fmlx *mlx)
{
	if (key == 53)
		fdf_exit(mlx);
	return (key);
}

void	fractol(void)
{
	t_fmlx	ptr;
	int		bpp;
	int		size_line;
	int		endian;

	if (!(ptr.mlx = mlx_init()))
		fdf_exit(&ptr);
	if (!(ptr.win = mlx_new_window(ptr.mlx, SWIN_X, SWIN_Y, "fractol - ")))
		fdf_exit(&ptr);
	if (!(ptr.img = mlx_new_image(ptr.mlx, SIMG_X, SIMG_Y)))
		fdf_exit(&ptr);
	if (!(ptr.screen = mlx_get_data_addr(ptr.img, &bpp, &size_line, &endian)))
		fdf_exit(&ptr);
	mlx_hook(ptr.win, 2, 0, deal_key, &ptr);
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
