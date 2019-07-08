/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 01:47:35 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/08 07:02:41 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		get_color(t_fmlx *mlx, int i)
{
	int	red;
	int	green;
	int	blue;

	i %= 225;
	if (mlx->colors == 0)
		return (0xFFFFFF);
	red = (i * 5) * 3;
	green = (255 - (i * 12)) * 3;
	blue = (255 - (i * 2)) * 3;
	return (((red & 0xFF) << 16) | ((green & 0xFF) << 8) | (blue & 0xFF));
}

void	print_controls(t_fmlx *mlx, int color)
{
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220,
			60, color, "+-----------------------");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220,
			80, color, "| colors: c");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220,
			100, color, "| switch: m | j | b");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220,
			120, color, "| +: p  -: l");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220,
			140, color, "| hide: clear");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220,
			160, color, "| reset: space");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220,
			180, color, "| (julia)edit: tab");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220,
			200, color, "| quit: esc");
	mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220,
			220, color, "+-----------------------");
}

void	print_ui(t_fmlx *mlx)
{
	static char	*fractals[FRACT_NUM] = {"mandelbrot", "julia", "burningship"};
	int			color;
	char		*tmp;
	char		*pmt;

	tmp = NULL;
	pmt = NULL;
	color = (mlx->colors == 1) ? 0xFFFFFF : 0xFF0000;
	if (mlx->hide_ui != 1)
	{
		mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220, 5,
				color, "+----------------------");
		mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220, 20,
				color, "| fractal=");
		mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 110, 20,
				color, fractals[mlx->fract]);
		mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 220, 40, color, "| zoom=");
		tmp = ft_itoa(mlx->zoom / 2.5);
		pmt = ft_strjoin(tmp, "%");
		ft_strdel(&tmp);
		if (pmt)
			mlx_string_put(mlx->mlx, mlx->win, SIMG_X - 130, 40, color, pmt);
		ft_strdel(&pmt);
		print_controls(mlx, color);
	}
}
