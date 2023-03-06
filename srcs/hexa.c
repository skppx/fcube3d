/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:28:28 by repinat           #+#    #+#             */
/*   Updated: 2023/03/06 14:48:00 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hex_2(int r, int g, int b)
{
/*	char	hex_chars[] = "0123456789abcdef";

	hex = malloc(8 * sizeof(char));
	if (!hex)
		return (NULL);
	hex[0] = '#';
	hex[1] = hex_chars[r / 16];
	hex[2] = hex_chars[r % 16];
	hex[3] = hex_chars[g / 16];
	hex[4] = hex_chars[g % 16];
	hex[5] = hex_chars[b / 16];
	hex[6] = hex_chars[b % 16];
	hex[7] = '\0';*/
	
	return (0 << 24 | r << 16 | g << 8 | b);
}

int	rgb_to_hex(char **rgb)
{
	int r;
	int	g;
	int	b;
	
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_tab(rgb);
	
	return (0 << 24 | r << 16 | g << 8 | b);
}
