/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:33:53 by repinat           #+#    #+#             */
/*   Updated: 2023/02/09 16:49:43 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	ft_parsing_arg(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error, wrong number of arguments\n", 1);
		return (0);
	}
	if (!check_extension(av[1]))
		return (0);
	// if (!check_char(av[1]))
	// 	return (0);
	return (1);
}