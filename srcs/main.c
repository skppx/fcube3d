/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:09:16 by repinat           #+#    #+#             */
/*   Updated: 2023/02/09 16:52:18 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_map(char **av, t_vars *cub)
{
	char	*tmp;
	int		fd;
	int		i;

	fd = open(av[1], O_RDONLY);
	i = 0;
	while (i < 2)
	{
		tmp = get_next_line(fd);
		cub->map[i] = tmp;
		free(tmp);
		i++;
	}
	cub->map[i] = 0;

	//

	i = 0;
	while (cub->map[i])
	{
		printf("%s\n", cub->map[i]);
		i++;
	}
}

int main(int ac, char **av)
{
	t_vars	cub;
	
	if (!ft_parsing_arg(ac, av))
		return (0);
	open_map(av, &cub);
	return (0);
}