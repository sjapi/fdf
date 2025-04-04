/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:38:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/04 20:16:14 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>

typedef struct s_landscape
{
	int	**mtrx;
	int	x_len;
	int	y_len;
}	t_landscape;

int			ft_atoi(char *str);

void		ft_putstr(char *str);

char		*get_file_content(char *path);

t_landscape	*init_landscape(char *str);

#endif
