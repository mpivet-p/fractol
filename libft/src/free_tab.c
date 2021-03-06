/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 00:06:49 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/07/02 01:35:13 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_tab(char ***tab)
{
	char	**ptr;
	int		i;

	i = 0;
	if (tab && *tab)
	{
		ptr = *tab;
		while (ptr[i] != 0)
		{
			ft_strdel(&(ptr[i]));
			i++;
		}
		free(*tab);
		i++;
		*tab = NULL;
	}
}
