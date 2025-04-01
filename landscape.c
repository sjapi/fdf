/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   landscape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:39:55 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/01 18:59:36 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static int	get_x_len(char *str)
{
	int	x_len;

	x_len = 0;
	while (*str && *str == ' ')
	{
		str++;
	}
	while (*str != '\n' && *str != '\0')
	{
		while (*str && (*str == '-' || (*str >= '0' && *str <= '9')))
		{
			str++;
		}
		while (*str && *str == ' ')
		{
			str++;
		}
		x_len += 1;
	}
	return (x_len);
}

static int	get_y_len(char *str)
{
	int	y_len;

	y_len = 0;
	while (*str)
	{
		if (*str == '\n')
		{	
			y_len += 1;
		}
		str++;
	}
	return (y_len);
}

static void	free_mtrx(int **mtrx, int i)
{
	(void)mtrx;
	(void)i;
}

static int	fill_mtrx(t_landscape *l, char *str)
{
	(void)l;
	(void)str;
	return (0);
}

t_landscape	*create_landscape(char *str)
{
	t_landscape	*l;
	int			i;

	l = malloc(sizeof(t_landscape));
	if (!l)
		return (NULL);
	l->x_len = get_x_len(str);
	l->y_len = get_y_len(str);
	l->mtrx = malloc(sizeof(int *) * l->y_len);
	if (!l->mtrx)
		return (free(l), NULL);
	i = 0;
	while (i < l->y_len)
	{
		l->mtrx[i] = malloc(sizeof(int) * l->x_len);
		if (!l->mtrx[i])
			return (free_mtrx(l->mtrx, i), free(l), NULL);
		i++;
	}
	if (fill_mtrx(l, str) == -1)
		return (free_mtrx(l->mtrx, l->y_len), free(l), NULL);
	return (l);
}
