/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 00:33:40 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/08 06:54:19 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	burningship(t_fmlx *mlx, t_point coords)
{
	t_cplx	c;
	t_cplx	z;
	int		i;
	double	tmp;

	c.rl = coords.x / mlx->zoom + mlx->xmin;
	c.im = coords.y / mlx->zoom + mlx->ymin;
	z.rl = c.rl;
	z.im = c.im;
	tmp = 0;
	i = 0;
	while (((z.rl * z.rl) + (z.im * z.im)) < 4 && i < mlx->max_inter)
	{
		tmp = (z.rl * z.rl) - (z.im * z.im) + c.rl;
		z.im = fabs(2 * z.rl * z.im) + c.im;
		z.rl = fabs(tmp);
		i++;
	}
	if (i != mlx->max_inter)
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y),
				get_color(mlx, i));
}

void	init_burningship(t_fmlx *mlx)
{
	mlx->max_inter = 15;
	mlx->xmin = -2.5;
	mlx->ymin = -2;
	mlx->zoom = 250;
	mlx->fract = FRACT_BURNING;
}
