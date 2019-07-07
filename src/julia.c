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
	mlx->julia.rl = 0.285;
	mlx->julia.im = 0.01;
	mlx->julia_edit = 0;
}

void	julia_edit(t_fmlx *mlx, int x, int y)
{
	double xmod;
	double ymod;

	x *= 0.55;
	y *= 0.55;
	xmod = log((x % (SIMG_X / 2)) / 10) / 5;
	if (xmod < 0.01)
		xmod = 0.01;
	ymod = log((y % (SIMG_Y / 2)) / 15) / 10;
	if (ymod < 0.01)
		ymod = 0.01;
	mlx->julia.rl = (x > (SIMG_X / 2)) ? xmod : xmod * -1 ;
	mlx->julia.im = (y > (SIMG_Y / 2)) ? ymod : ymod * -1 ;
	printf("%i %i \n", x, y);
	disp_fractol(mlx);
}
