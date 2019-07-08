/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 04:49:56 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/08 04:51:50 by mpivet-p         ###   ########.fr       */
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

void	fractol_exit(t_fmlx *mlx)
{
	if (mlx->mlx && mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->mlx && mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}
