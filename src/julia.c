#include "fractol.h"

void	julia(t_fmlx *mlx, t_point coords)
{
	t_cplx c;
	t_cplx z;
	int i;
	double tmp;

	c.rl = 0.285;
	c.im = 0.01;
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
	if (i == mlx->max_inter)
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), 0);
	else
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), ((i * 255 / mlx->max_inter) << 16));
}

void	init_julia(t_fmlx *mlx)
{
	mlx->max_inter = 60;
	mlx->xmin = -1;
	mlx->xmax = 1;
	mlx->ymin = -1.2;
	mlx->ymax = 1.2;
	mlx->zoom = 100;
	mlx->fract = FRACT_JULIA;
}
