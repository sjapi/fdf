/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:02:34 by azolotar          #+#    #+#             */
/*   Updated: 2025/04/17 15:41:24 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	interpolate(int start, int end, float rel_pos)
{
	return ((int)(start + (end - start) * rel_pos));
}

int	get_gradient_color(int start, int end, float rel_pos)
{
	int	r;
	int	g;
	int	b;

	r = interpolate((start >> 16) & 0xff, (end >> 16) & 0xff, rel_pos);
	g = interpolate((start >> 8) & 0xff, (end >> 8) & 0xff, rel_pos);
	b = interpolate(start & 0xff, end & 0xff, rel_pos);
	return ((r << 16) | (g << 8) | (b << 0));
}
