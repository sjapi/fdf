/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:39:55 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/14 17:59:39 by azolotar         ###   ########.fr       */
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

void	free_map(t_map *m, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(m->mtrx[j]);
		j++;
	}
	free(m->mtrx);
	free(m);
}

static void	fill_mtrx_line(t_map *m, char *str, int line)
{
	int	i;

	i = 0;
	while (*str != '\0' && *str != '\n')
	{
		m->mtrx[line][i] = ft_atoi(str);
		i++;
		while (*str && *str == ' ')
			str++;
		if (*str && *str == '-')
			str++;
		while (*str && *str >= '0' && *str <= '9')
			str++;
	}
}

static int	fill_mtrx(t_map *m, char *path)
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
		if (!line && i == m->y_len)
			break ;
		else if (!line && i != m->y_len)
			return (-1);
		fill_mtrx_line(m, line, i);
		free(line);
		i++;
	}
	return (0);
}

t_map	*init_map(char *path)
{
	char		*content;
	t_map		*m;
	int			i;

	content = get_file_content(path);
	m = malloc(sizeof(t_map));
	if (!content || !m)
		return (NULL);
	m->x_len = get_x_len(content);
	m->y_len = get_y_len(content);
	free(content);
	m->mtrx = malloc(sizeof(int *) * m->y_len);
	if (!m->mtrx)
		return (free(m), NULL);
	i = 0;
	while (i < m->y_len)
	{
		m->mtrx[i] = malloc(sizeof(int) * m->x_len);
		if (!m->mtrx[i])
			return (free_map(m, i), NULL);
		i++;
	}
	if (fill_mtrx(m, path) == -1)
		return (free_map(m, m->y_len), NULL);
	return (m);
}

void	debug_print(t_map *m)
{
	int	i;
	int	j;

	printf("x: %d\n", m->x_len);
	printf("y: %d\n", m->y_len);
	i = 0;
	while (i < m->y_len)
	{
		j = 0;
		while (j < m->x_len)
		{
			printf("%5d ", m->mtrx[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
