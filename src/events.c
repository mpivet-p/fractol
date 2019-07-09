/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:54:43 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/09 01:58:12 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	arrow_moves(t_fmlx *mlx, int key)
{
	if (key == 123)
		mlx->xmin += (25 / mlx->zoom);
	else if (key == 124)
		mlx->xmin -= (25 / mlx->zoom);
	else if (key == 125)
		mlx->ymin -= (25 / mlx->zoom);
	else if (key == 126)
		mlx->ymin += (25 / mlx->zoom);
}

int		deal_key(int key, t_fmlx *mlx)
{
	if (key == 35)
		mlx->max_inter += 2;
	else if (key == 37 && mlx->max_inter > 1)
		mlx->max_inter -= 2;
	else if (key == 53)
		fractol_exit(mlx);
	else if ((key == 49 && mlx->fract == 0) || (key == 46 && mlx->fract != 0))
		init_mandelbrot(mlx);
	else if ((key == 49 && mlx->fract == 1) || (key == 38 && mlx->fract != 1))
		init_julia(mlx);
	else if ((key == 49 && mlx->fract == 2) || (key == 11 && mlx->fract != 2))
		init_burningship(mlx);
	else if (mlx->fract == FRACT_JULIA && key == 48)
		mlx->julia_edit = (mlx->julia_edit == 1) ? 0 : 1;
	else if (key == 8 && mlx->colors != 0)
		mlx->colors = 0;
	else if (key == 71)
		mlx->hide_ui ^= 1;
	else if (key == 8 || key == 69)
		mlx->colors++;
	else
		arrow_moves(mlx, key);
	disp_fractol(mlx);
	return (key);
}

int		mouse_roll(int button, int x, int y, t_fmlx *mlx)
{
	if (button == 5)
	{
		zoom_up(mlx, x, y);
		mlx->zoom++;
	}
	if (button == 4)
	{
		zoom_down(mlx, x, y);
		mlx->zoom--;
	}
	return (button);
}

int		mouse_move(int x, int y, t_fmlx *mlx)
{
	if (mlx->fract == FRACT_JULIA && mlx->julia_edit == 1)
		julia_edit(mlx, x, y);
	return (0);
}
