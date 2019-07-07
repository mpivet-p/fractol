/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/07 03:09:43 by mpivet-p         ###   ########.fr       */
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

void	disp_fractol(t_fmlx *mlx)
{
	static void	(*fractal[FRACT_NUM])(t_fmlx *mlx, t_point coords) = {mandelbrot, julia};
	t_point		coords;
	int			i;

	coords.x = 0;
	coords.y = 0;
	i = -1;
	ft_bzero(mlx->screen, (SIMG_X * SIMG_Y) * 4);
	while (coords.x < SIMG_X)
	{
		while (coords.y < SIMG_Y)
		{
			i = -1;
			while (++i < FRACT_NUM)
				if (i == mlx->fract)
					fractal[i](mlx, coords);
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

void	fractol(int type)
{
	t_fmlx	ptr;
	int		bpp;
	int		size_line;
	int		endian;

	if (type == FRACT_MANDEL)
		init_mandelbrot(&ptr);
	else if (type == FRACT_JULIA)
		init_julia(&ptr);
	else
		exit(1);
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
	mlx_hook(ptr.win, 6, 0, mouse_move, &ptr);
	disp_fractol(&ptr);
	mlx_loop(ptr.mlx);
}

int		get_fractal(char *name)
{
	static char *fractals[FRACT_NUM] = {"mandel", "julia"};
	int i;

	i = 0;
	while (i < FRACT_NUM)
	{
		if (ft_strcmp(name, fractals[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		main(int argc, char **argv)
{
	int type;

	type = (argc == 2) ? get_fractal(argv[1]) : -1;
	if (type == -1)
	{
		ft_putstr_fd("usage : fractol < mandel | julia | koch >\n", 2);
		return (1);
	}
	fractol(type);
	return (0);
}
