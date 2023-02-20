/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:09:16 by repinat           #+#    #+#             */
/*   Updated: 2023/02/20 15:26:56 by repinat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*nord_texture(char *str, int i, t_vars *cub)
{
	char	*dup;

	cub->count_l++;
	while (str[i] && str[i] != '.')
		i++;
	dup = ft_strdup(&str[i]);
	return (dup);
}

void	*south_texture(char *str, int i, t_vars *cub)
{
	char	*dup;
	
	cub->count_l++;
	while (str[i] && str[i] != '.')
		i++;
	dup = ft_strdup(&str[i]);
	return (dup);
}

void	*west_texture(char *str, int i, t_vars *cub)
{
	char	*dup;

	cub->count_l++;
	while (str[i] && str[i] != '.')
		i++;
	dup = ft_strdup(&str[i]);
	return (dup);
}

void	*east_texture(char *str, int i, t_vars *cub)
{
	char	*dup;

	cub->count_l++;
	while (str[i] && str[i] != '.')
		i++;
	dup = ft_strdup(&str[i]);
	return (dup);
}

void	*ground_rgb(char *str, int i, t_vars *cub)
{
	char	*dup;

	cub->count_l++;
	while (str[i] && !(ft_isdigit(str[i])))
		i++;
	dup = ft_strdup(&str[i]);
	return (dup);
}

void	*sky_rgb(char *str, int i, t_vars *cub)
{
	char	*dup;

	cub->count_l++;
	while (str[i] && !(ft_isdigit(str[i])))
		i++;
	dup = ft_strdup(&str[i]);
	return (dup);
}

int	sorting_data(char **map, t_vars *cub)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < 7)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] == 'N' && map[i][j + 1] == 'O' && map[i][j + 2] == ' ')
			cub->wall_N = nord_texture(map[i], j, cub);
		if (map[i][j] == 'S' && map[i][j + 1] == 'O' && map[i][j + 2] == ' ')
			cub->wall_S = south_texture(map[i], j, cub);
		if (map[i][j] == 'W' && map[i][j + 1] == 'E' && map[i][j + 2] == ' ')
			cub->wall_W = west_texture(map[i], j, cub);
		if (map[i][j] == 'E' && map[i][j + 1] == 'A' && map[i][j + 2] == ' ')
			cub->wall_E = east_texture(map[i], j, cub);
		if (map[i][j] == 'F')
			cub->ground = ground_rgb(map[i], j, cub);
		if (map[i][j] == 'C')
			cub->sky = sky_rgb(map[i], j, cub);
		i++;
	}
	if (cub->count_l != 6)
		return (0);
	return (1);
}

void	open_file(char **av, t_vars *cub)
{
	char	*line;
	char	*tmp;
	int		fd;
	int		size;

	size = 0;
	tmp = NULL;
	line = NULL;
	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		tmp = ft_strjoin(tmp, line);
		if (line[0] != '\n')
			size++;
		free(line);
	}
	cub->size_map = size - 1;
	cub->map = malloc((size + 1) * sizeof(char *));
	cub->map = ft_split(tmp, '\n');
	free(tmp);
	close(fd);

//	affichage test

	// int i = 0;
	// while (cub->map[i] != NULL)
	// {
	// 	printf("%s\n", cub->map[i]);
	// 	i++;
	// }
	// printf("\n\n");
}

void	set_map(t_vars *cub)
{
	char	**new_map;
	int		i;
	int		j;

	cub->size_map -= 6;
	new_map = malloc(cub->size_map * sizeof(char *));
	i = -1;
	j = 5;
	while ((size_t)++i < (cub->size_map + 1))
		new_map[i] = ft_strdup(cub->map[++j]);
	new_map[i] = NULL;
	free_tab(cub->map);
	cub->map = new_map;

	i = 0;
	while (cub->map[i] != NULL)
	{
		printf("%s\n", cub->map[i]);
		i++;
	}
	printf("\n\n");
}

int main(int ac, char **av)
{
	t_vars	cub;
	
	(void)ac;
	cub.count_l = 0;
	open_file(av, &cub);
	if (!(sorting_data(cub.map, &cub)))
	{
		printf("ERRRRROR\n");
		free_tab(cub.map);
		return (0);
	}
	set_map(&cub);
	if (!ft_parsing(ac, av, &cub))
	{
		printf("Error\n");
		free_tab(cub.map);
		return (0);
	}
	free_tab(cub.map);

	free(cub.wall_N);
	free(cub.wall_S);
	free(cub.wall_E);
	free(cub.wall_W);
	free(cub.ground);
	free(cub.sky);

	return (0);
}