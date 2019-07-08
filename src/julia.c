/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 06:54:24 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/08 06:54:39 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_fmlx *mlx, t_point coords)
{
	t_cplx	c;
	t_cplx	z;
	int		i;
	double	tmp;

	c.rl = mlx->julia.rl;
	c.im = mlx->julia.im;
	z.rl = coords.x / mlx->zoom + mlx->xmin;
	z.im = coords.y / mlx->zoom + mlx->ymin;
	tmp = 0;
	i = 0;
	while (((z.rl * z.rl) + (z.im * z.im)) < 4 && i < mlx->max_inter)
	{
		tmp = z.rl;
		z.rl = (z.rl * z.rl) - (z.im * z.im) + c.rl;
		z.im = 2 * z.im * tmp + c.im;
		i++;
	}
	if (i != mlx->max_inter)
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y),
				get_color(mlx, i));
}

void	init_julia(t_fmlx *mlx)
{
	mlx->max_inter = 60;
	mlx->xmin = -2;
	mlx->ymin = -1.65;
	mlx->zoom = 250;
	mlx->fract = FRACT_JULIA;
	mlx->julia.rl = -0.765;
	mlx->julia.im = -0.07;
	mlx->julia_edit = 0;
}

void	julia_edit(t_fmlx *mlx, int x, int y)
{
	double mod;

	(void)y;
	x += 680;
	mod = -1 + (1.5 * (double)x / SIMG_X * 0.5);
	mlx->julia.im = mod;
	disp_fractol(mlx);
}
