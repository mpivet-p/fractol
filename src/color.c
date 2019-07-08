/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 01:47:35 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/08 05:36:57 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		get_color(t_fmlx * mlx, int i)
{
	int     red;
	int     green;
	int     blue;

	i %= 225;
	if (mlx->colors == 0)
		return (0xFFFFFF);
	red = (i * 5) * 3;
	green = (255 - (i * 12)) * 3;
	blue = (255 - (i * 2)) * 3;
	return (((red & 0xFF) << 16) | ((green & 0xFF) << 8) | (blue & 0xFF));
}

void	print_controls(t_fmlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 100,
			SIMG_Y - 5, color, "+-----------------------");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 100,
			SIMG_Y - 25, color, "| colors: c");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 100,
			SIMG_Y - 25, color, "| switch: m | j | b");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 100,
			SIMG_Y - 25, color, "| +: p  -: l");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 100,
			SIMG_Y - 25, color, "| hide: clear");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 100,
			SIMG_Y - 5, color, "+-----------------------");
}

void	print_ui(t_fmlx *mlx)
{
	static char	*fractals[FRACT_NUM] = {"mandelbrot", "julia", "burningship"}
	int			color;
	char		*tmp;
	char		*pmt;

	tmp = NULL;
	ptm = NULL;
	color = (mlx->colors == 1) ? 0xFFFFFF : 0xFF0000;
	if (mlx->hide_ui != 1)
	{
		mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 100, SIMG_Y - 5, color, "+----------------------");
		mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 100, SIMG_Y - 25, color, "| fractal=");
		mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 50, SIMG_Y - 25, color, fractals[mlx->fract]);
		mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 100, SIMG_Y - 25, color, "| zoom=");
		tmp = ft_atoi(mlx->zoom / 25);
		ptm = ft_strjoin(tmp, " %");
		ft_strdel(tmp);
		if (pmt)
			mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 50, SIMG_Y - 25, color, pmt);
		ft_strdel(pmt);
		print_controls(mlx);
	}
}
