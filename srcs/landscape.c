/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   landscape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:39:55 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/09 17:21:01 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"
#include <stdlib.h>
#include "libft.h"
#include <fcntl.h>

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

void	free_landscape(t_landscape *l, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(l->mtrx[j]);
		j++;
	}
	free(l->mtrx);
	free(l);
}

static void	fill_mtrx_line(t_landscape *l, char *str, int line)
{
	int	i;

	i = 0;
	while (*str != '\0' && *str != '\n')
	{
		l->mtrx[line][i] = ft_atoi(str);
		i++;
		while (*str && *str == ' ')
			str++;
		if (*str && *str == '-')
			str++;
		while (*str && *str >= '0' && *str <= '9')
			str++;
	}
}

static int	fill_mtrx(t_landscape *l, char *path)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line && i == l->y_len)
			break ;
		else if (!line && i != l->y_len)
			return (-1);
		fill_mtrx_line(l, line, i);
		free(line);
		i++;
	}
	return (0);
}

t_landscape	*init_landscape(char *path)
{
	char		*content;
	t_landscape	*l;
	int			i;

	content = get_file_content(path);
	l = malloc(sizeof(t_landscape));
	if (!content || !l)
		return (NULL);
	l->x_len = get_x_len(content);
	l->y_len = get_y_len(content);
	free(content);
	l->mtrx = malloc(sizeof(int *) * l->y_len);
	if (!l->mtrx)
		return (free(l), NULL);
	i = 0;
	while (i < l->y_len)
	{
		l->mtrx[i] = malloc(sizeof(int) * l->x_len);
		if (!l->mtrx[i])
			return (free_landscape(l, i), NULL);
		i++;
	}
	if (fill_mtrx(l, path) == -1)
		return (free_landscape(l, l->y_len), NULL);
	return (l);
}
