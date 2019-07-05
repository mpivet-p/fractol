//HEADER

#include "fractol.h"

void	zoom_up(t_fmlx *mlx)
{
	mlx->max_inter += 2;
	mlx->xmin *= 0.9;
	mlx->xmax *= 0.9;
	mlx->ymin *= 0.9;
	mlx->ymax *= 0.9;
	disp_fractol(mlx);
}

void	zoom_down(t_fmlx *mlx)
{
	if (mlx->max_inter > 1)
	{
		mlx->max_inter -= 2;
		mlx->xmin *= 1.1;
		mlx->xmax *= 1.1;
		mlx->ymin *= 1.1;
		mlx->ymax *= 1.1;
		disp_fractol(mlx);
	}
}
