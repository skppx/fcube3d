/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:09:16 by repinat           #+#    #+#             */
/*   Updated: 2023/02/13 16:52:32 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_size(char **av)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(av[1], O_RDONLY);
	i = -1;
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		i++;
	}
	close(fd);
	return (i + 2);
}

void	open_map(char **av, t_vars *cub)
{
	char	*line;
	char	*tmp;
	int		fd;
//	int		i;

	tmp = NULL;
	line = NULL;
	cub->map = malloc(map_size(av) * sizeof(char *));
	fd = open(av[1], O_RDONLY);
//	i = -1;
	while ((line = get_next_line(fd)) != NULL)
	{
		tmp = ft_strjoin(tmp, line);
		free(line);
	}
	cub->map = ft_split(tmp, '\n');
	close(fd);

//	affichage test

	// int i = 0;
	// while (cub->map[i] != NULL)
	// {
	// 	printf("%s\n", cub->map[i]);
	// 	i++;
	// }
}

int main(int ac, char **av)
{
	t_vars	cub;
	
	(void)ac;
	open_map(av, &cub);
	if (!ft_parsing(ac, av, &cub))
	{
		printf("Error\n");
		return (0);
	}
	free_tab(cub.map);
	return (0);
}