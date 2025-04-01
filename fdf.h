/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:38:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/01 18:06:31 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_landscape
{
	int	*mtrx;
	int	x_len;
	int	y_len;
}	t_landscape;

void		ft_putstr(char *str);

char		*get_file_content(char *path);

t_landscape	*create_landscape(char *str);

#endif
