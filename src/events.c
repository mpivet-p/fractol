#include "fractol.h"

int		deal_key(int key, t_fmlx *mlx)
{
	if (key == 35)
		mlx->max_inter += 2;
	else if  (key == 37 && mlx->max_inter > 1)
		mlx->max_inter -= 2;
	else if (key == 53)
		fractol_exit(mlx);
	else if (key == 49)
	{
		if (mlx->fract == 'm')
			init_mandelbrot(mlx);
		else if  (mlx->fract == 'j')
			init_julia(mlx);
	}
	else if (key == 125)
	{
		mlx->ymin += 1 / (double)mlx->zoom; 
		mlx->ymax += 1 / (double)mlx->zoom;
	}
	else if (key == 126)
	{
		mlx->ymin -= 1 / (double)mlx->zoom;
		mlx->ymax -= 1 / (double)mlx->zoom;
	}
	disp_fractol(mlx);
	return (key);
}

int		test_mouse(int button, int x, int y, t_fmlx *mlx)
{
	(void)mlx;
	(void)x;
	(void)y;
	if (button == 5)
	{
		zoom_up(mlx);
		mlx->zoom++;
	}
	if (button == 4)
	{
		zoom_down(mlx);
		mlx->zoom--;
	}
	return (button);
}
