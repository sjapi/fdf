/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:01:12 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/17 18:06:23 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

void	free_map(t_map *m, int y)
{
	int	i;

	i = -1;
	while (++i < y)
		free(m->mtrx[i]);
	free(m->mtrx);
	free(m);
}

static int	get_x_len(char **lines)
{
	int		x_len;
	char	**split;
	int		i;

	i = -1;
	x_len = INT_MAX;
	while (lines[++i] != 0)
	{
		split = ft_split(lines[i], ' ');
		x_len = ft_min(ft_split_count(split), x_len);
		ft_free_split(split);
	}
	return (x_len);
}

static int	fill_mtrx_line(t_map *m, int y, char **split)
{
	int		x;
	char	**num_and_color;

	x = -1;
	while (++x < m->x_len)
	{
		if (ft_contains(split[x], ','))
		{
			num_and_color = ft_split(split[x], ',');
			if (!num_and_color)
				return (0);
			m->mtrx[y][x].value = ft_atoi(num_and_color[0]);
			m->mtrx[y][x].color = ft_atoi_base(num_and_color[1] + 2,
					"0123456789abcdef");
			if (!m->mtrx[y][x].color)
				m->mtrx[y][x].color = ft_atoi_base(num_and_color[1] + 2,
						"0123456789ABCDEF");
			ft_free_split(num_and_color);
			continue ;
		}
		m->mtrx[y][x].value = ft_atoi(split[x]);
		m->mtrx[y][x].color = 0xffffff;
	}
	return (1);
}

static int	fill_map_mtrx(t_map *m, char **lines)
{
	int		y;
	char	**split;

	y = -1;
	m->mtrx = malloc(sizeof(t_map_point *) * m->y_len);
	if (!m->mtrx)
		return (free_map(m, 0), 0);
	while (lines[++y])
	{
		m->mtrx[y] = malloc(sizeof(t_map_point) * m->x_len);
		if (!m->mtrx[y])
			return (free_map(m, y), 0);
		split = ft_split(lines[y], ' ');
		if (!split)
			return (0);
		if (!fill_mtrx_line(m, y, split))
			return (ft_free_split(split), 0);
		ft_free_split(split);
	}
	return (1);
}

t_map	*init_map(char *path)
{
	char		*content;
	char		**lines;
	t_map		*m;

	content = get_file_content(path);
	if (!content)
		return (0);
	lines = ft_split(content, '\n');
	if (!lines)
		return (0);
	free(content);
	m = malloc(sizeof(t_map));
	if (!m)
		return (0);
	m->y_len = ft_split_count(lines);
	m->x_len = get_x_len(lines);
	if (!fill_map_mtrx(m, lines))
		return (ft_free_split(lines), free_map(m, m->y_len), NULL);
	ft_free_split(lines);
	return (m);
}
