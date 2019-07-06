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
		if (mlx->fract == 0)
			init_mandelbrot(mlx);
		else if  (mlx->fract == 1)
			init_julia(mlx);
	}
	disp_fractol(mlx);
	return (key);
}

int		test_mouse(int button, int x, int y, t_fmlx *mlx)
{
	(void)mlx;
	if (button == 5)
	{
		zoom_up(mlx, x, y);
		mlx->zoom++;
	}
	if (button == 4)
	{
		zoom_down(mlx, x, y);
		mlx->zoom--;
	}
	return (button);
}
