#include "fractol.h"

void	mandelbrot(t_fmlx *mlx, t_point coords)
{
	t_cplx c;
	t_cplx z;
	int i;
	double tmp;

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
	if (i == mlx->max_inter)
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), 0);
	else
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), 0xFFFFFF);
}

void	init_mandelbrot(t_fmlx *mlx)
{
	mlx->max_inter = 50;
	mlx->xmin = -2.7;
	mlx->xmax = 0.6;
	mlx->ymin = -1.7;
	mlx->ymax = 1.2;
	mlx->zoom = 250;
	mlx->fract = FRACT_MANDEL;
}