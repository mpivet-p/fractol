#include "fractol.h"

void	julia(t_fmlx *mlx, t_point coords)
{
	t_cplx c;
	t_cplx z;
	int i;
	double tmp;

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
		fill_pxl(mlx->screen, lround(coords.x), lround(coords.y), 0xFFFFFF);
}

void	init_julia(t_fmlx *mlx)
{
	mlx->max_inter = 60;
	mlx->xmin = -2;
	mlx->xmax = 1;
	mlx->ymin = -1.65;
	mlx->ymax = 1.2;
	mlx->zoom = 250;
	mlx->fract = FRACT_JULIA;
	mlx->julia.rl = -0.765;
	mlx->julia.im = -0.07;
	mlx->julia_edit = 0;
}

void	julia_edit(t_fmlx *mlx, int x, int y)
{
	double xmod;
	double ymod;

	xmod = -1.5 + (3 * (double)x / SIMG_X);
	ymod = -1.5 + (3 * (double)y / SIMG_Y);
	mlx->julia.rl = xmod;
	mlx->julia.im = ymod;
	printf("%f %f\n", mlx->julia.rl, mlx->julia.im);
	printf("%i %i \n", x, y);
	disp_fractol(mlx);
}
