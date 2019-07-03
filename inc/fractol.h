/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 01:32:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/02 03:10:53 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define SWIN_X 1000
# define SWIN_Y 800
# define SIMG_X 1000
# define SIMG_Y 800
# define MAX_INTERACT 50
# define FRACT_XA -2.1
# define FRACT_XB 0.6
# define FRACT_YA -1.2
# define FRACT_YB 1.2

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

typedef struct	s_cplx
{
	double rl;
	double im;
}				t_cplx;

typedef struct	s_fmlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*screen;
}				t_fmlx;

#endif
