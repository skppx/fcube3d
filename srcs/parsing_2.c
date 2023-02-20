/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:58:01 by repinat           #+#    #+#             */
/*   Updated: 2023/02/20 13:58:11 by repinat          ###   ########.fr       */
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
		if (!(map[0][i] == '1' || map[0][i] == ' '))
			return (0);
	}
	i = 0;
	while(map[i])
		i++;
	i--;
	j = -1;
	while(map[i][++j])
	{
		if (!(map[i][j] == '1' || map[i][j] == ' '))
			return (0);
	}
	return (1);
}

int	check_side(char **map, t_vars *cub)
{
	int		i;
	size_t	j;

	i = -1;
	while ((size_t)i < cub->size_map)
	{
		if (!(map[i][0] == '1' || map[i][0] == ' '))
			return (0);
	}
	i = 0;
	while ((size_t)i < cub->size_map)
	{
		j = ft_strlen(map[i]) - 1;
		if (map[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_side_2(char **map, t_vars *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (++i < cub->size_map)
	{
		if (ft_strlen(map[i]) > ft_strlen(map[i + 1]))
		{
			j = 0;
			while (j < ft_strlen(map[i + 1]))
				j++;
			while(j < ft_strlen(map[i]))
			{
				if (map[i][j] != '1')
					return (0);
				j++;
			}
		}
	}
	return (1);
}

int	check_space_2(char **map, size_t i, size_t j, t_vars *cub)
{
	if (i < cub->size_map && map[i + 1][j] == '0')
		return (0);
	if (i > 0 && map[i - 1][j] == '0')
		return (0);
	if (j < ft_strlen(map[i]) && map[i][j + 1] == '0')
		return (0);
	if (j > 0 && map[i][j - 1] == '0')
		return (0);
	if (i < cub->size_map && j < ft_strlen(map[i]) && map[i + 1][j + 1] == '0')
		return (0);
	if (i > 0 && j < ft_strlen(map[i]) && map[i - 1][j + 1] == '0')
		return (0);
	if (i < cub->size_map && j > 0 && map[i + 1][j - 1] == '0')
		return (0);
	if (i > 0 && j > 0 && map[i - 1][j - 1] == '0')
		return (0);
	return (1);
}

int	check_space(char **map, t_vars *cub)
{
	int		i;
	int		j;

	i = 0;
	while ((size_t)i < cub->size_map)
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
			{
				if (!check_space_2(map, (size_t)i, (size_t)j, cub))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	closed_map(char	**map, t_vars *cub)
{
	if (!check_top_bot(map))
		return (0);
	if (!check_side(map, cub))
		return (0);
	if (!check_side_2(map, cub))
		return (0);
	if (!check_space(map, cub))
		return (0);
	return (1);
}