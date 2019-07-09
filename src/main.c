/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 00:26:11 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/09 03:31:10 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	disp_fractol(t_fmlx *mlx)
{
	fractol_loop(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	print_ui(mlx);
}

void	fractol_loop(t_fmlx *mlx, int i)
{
	static void	(*fractal[FRACT_NUM])(t_fmlx *mlx,
			t_point coords) = {mandelbrot, julia, burningship};
	t_point		coords;

	ft_bzero(mlx->screen, (SIMG_X * SIMG_Y) * 4);
	while (i < SIMG_X * SIMG_Y)
	{
		coords.x = i / SIMG_Y;
		coords.y = i % SIMG_Y;
		fractal[mlx->fract](mlx, coords);
		i++;
	}
}

void	fractol(int type)
{
	static void	(*func[FRACT_NUM + 1])(t_fmlx *mlx) = {init_mandelbrot,
		init_julia, init_burningship, fractol_exit};
	t_fmlx		ptr;
	int			tools[3];

	ptr.colors = 0;
	ptr.hide_ui = 0;
	func[type](&ptr);
	if (!(ptr.mlx = mlx_init()))
		fractol_exit(&ptr);
	if (!(ptr.win = mlx_new_window(ptr.mlx, SWIN_X,
					SWIN_Y, "fractol by mpivet-p")))
		fractol_exit(&ptr);
	if (!(ptr.img = mlx_new_image(ptr.mlx, SIMG_X, SIMG_Y)))
		fractol_exit(&ptr);
	if (!(ptr.screen = mlx_get_data_addr(ptr.img, &(tools[0]),
					&(tools[1]), &(tools[2]))))
		fractol_exit(&ptr);
	mlx_hook(ptr.win, 2, 0, deal_key, &ptr);
	mlx_hook(ptr.win, 4, 0, mouse_roll, &ptr);
	mlx_hook(ptr.win, 6, 0, mouse_move, &ptr);
	disp_fractol(&ptr);
	mlx_loop(ptr.mlx);
}

int		get_fractal(char *name)
{
	static char	*fractals[FRACT_NUM] = {"mandelbrot", "julia", "burningship"};
	int			i;

	i = 0;
	while (i < FRACT_NUM)
	{
		if (ft_strcmp(name, fractals[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		main(int argc, char **argv)
{
	int type;

	type = (argc == 2) ? get_fractal(argv[1]) : -1;
	if (type == -1)
	{
		ft_putstr_fd("usage: fractol <mandelbrot | julia | burningship>\n", 2);
		return (1);
	}
	fractol(type);
	return (0);
}
