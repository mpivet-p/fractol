/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 00:33:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/08 06:56:25 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_fmlx *mlx, t_point coords)
{
	t_cplx	c;
	t_cplx	z;
	double	tmp;
	int		i;

	c.rl = coords.x / mlx->zoom + mlx->xmin;
	c.im = coords.y / mlx->zoom + mlx->ymin;
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
	if (i != mlx->max_inter)
		fill_pxl(mlx->screen, lround(coords.x),
				lround(coords.y), get_color(mlx, i));
}

void	init_mandelbrot(t_fmlx *mlx)
{
	mlx->max_inter = 50;
	mlx->xmin = -2.7;
	mlx->ymin = -1.7;
	mlx->zoom = 250;
	mlx->fract = FRACT_MANDEL;
}
