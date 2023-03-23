/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:33:53 by repinat           #+#    #+#             */
/*   Updated: 2023/02/23 16:04:51 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	one_player(char **map)
{
	int i;
	int j;
	int count;

	count = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				count++;
		}
	}
	if (count != 1)
		return (0);
	return (1);
}

int	check_char(char **map)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!(map[i][j] == '0' || map[i][j] == '1' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == ' '))
				return (0);
		}
	}
	return (1);
}

//check le .cub
int	check_extension(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (str[i] != '.')
		i--;
	if (i == 0)
	{
		ft_putstr_fd("Invalid map name\n", 1);
		return (0);
	}
	if (!(str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b'))
	{
		ft_putstr_fd("Invalid map name\n", 1);
		return (0);
	}
	else
		return (1);
}

int	ft_parsing(int ac, char **av, t_vars *cub)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error, wrong number of arguments\n", 1);
		return (0);
	}
	if (!check_extension(av[1]))
		return (0);
	if (!check_char(cub->map))
	{
		ft_putstr_fd("Error, bad character(s) in map\n", 1);
		return (0);
	}
	if (!one_player(cub->map))
	{
	
		return (0);
	}
	if (!closed_map(cub->map, cub))
		return (0);
	return (1);
}
