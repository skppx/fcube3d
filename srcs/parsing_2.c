/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:58:01 by repinat           #+#    #+#             */
/*   Updated: 2023/02/13 17:24:10 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_top_bot(char **map)
{
	int	i;
	int	j;

	i = -1;
	while(map[0][++i])
	{
		if (map[0][i] != '1' || map[0][i] != ' ')
			return (0);
	}
	i = 0;
	while(map[i])
		i++;
	j = - 1
	while(map[i][++j])
	{
		if (map[i][j] != '1' || map[i][j] != ' ')
			return (0);
	}
	return (1);
}

int	check_side(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i][0])
	{
		if (map[i][0] != '1' || map[i][0] != ' ')
			return (0);
	}
	i = -1;
	while (map[++i][j])
	{
		j = -1;
		while (map[i][++j] && (map[i][++j] != ' '))
		{
			if (map[i][j] != '1')
				return (0);
		}
	}
	return (1);
}

int	check_space_2(char **map, int i, int j)
{
	//gauche
	if (j == 0 && (map[i][j - 1] != ' ' || map[i][j - 1] != '1'))
		return (0);
	//droite
	if (j )
}

int	check_space(char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i][j])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
			{
				if (!check_space_2(map, i, j))
					return (0);
			}
		}
	}
	return (1);
}

int	closed_map(char	**map)
{
	if (!check_top_bot(map))
		return (0);
	if (!check_side(map))
		return (0);
	if (!check_space(map))
		return (0);
}