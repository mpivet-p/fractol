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

void	disp_fractol(t_fmlx *mlx)
{
	t_point coords;
	t_point zoom;

	coords.x = 0;
	coords.y = 0;
	zoom.x = SIMG_X / (mlx->xmax - mlx->xmin);
	zoom.y = SIMG_Y / (mlx->ymax - mlx->ymin);
	printf("%i\n", mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 37, 5, 0xFFFFFF, "..."));
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
