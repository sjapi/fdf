/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:38:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/03/31 19:25:03 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_landspace
{
	int	*mtrx;
	int	x_len;
	int	y_len;
}	t_landspace;

void	ft_putstr(char *str);

char	*get_file_content(char *path);

#endif
