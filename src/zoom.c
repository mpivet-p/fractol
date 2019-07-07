/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 03:12:14 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/07 01:06:31 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_up(t_fmlx *mlx, int x, int y)
{
	mlx->max_inter += 2;
	mlx->xmin = (x / mlx->zoom + mlx->xmin) - (x / (mlx->zoom * 1.3));
	mlx->ymin = (y / mlx->zoom + mlx->ymin) - (y / (mlx->zoom * 1.3));
	mlx->zoom *= 1.3;
	disp_fractol(mlx);
}

void	zoom_down(t_fmlx *mlx, int x, int y)
{
	if (mlx->zoom > 100)
	{
		mlx->max_inter += 2;
		mlx->xmin = (x / mlx->zoom + mlx->xmin) - (x / (mlx->zoom / 1.3));
		mlx->ymin = (y / mlx->zoom + mlx->ymin) - (y / (mlx->zoom / 1.3));
		mlx->zoom /= 1.3;
		disp_fractol(mlx);
	}
}
