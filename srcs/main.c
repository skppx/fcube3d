/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:09:16 by repinat           #+#    #+#             */
/*   Updated: 2023/03/02 17:10:24 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*nord_texture(char *str, int i, t_vars *cub)
{
	char	*dup;

	cub->count_l++;
	while (str[i] && str[i] != '.')
		i++;
	dup = ft_strdup(&str[i]);
	// printf("%s\n", dup);
	return (dup);
}

char	*south_texture(char *str, int i, t_vars *cub)
{
	char	*dup;
	
	cub->count_l++;
	while (str[i] && str[i] != '.')
		i++;
	dup = ft_strdup(&str[i]);
	// printf("%s\n", dup);
	return (dup);
}

char	*west_texture(char *str, int i, t_vars *cub)
{
	char	*dup;

	cub->count_l++;
	while (str[i] && str[i] != '.')
		i++;
	dup = ft_strdup(&str[i]);
	// printf("%s\n", dup);
	return (dup);
}

char	*east_texture(char *str, int i, t_vars *cub)
{
	char	*dup;

	cub->count_l++;
	while (str[i] && str[i] != '.')
		i++;
	dup = ft_strdup(&str[i]);
	// printf("%s\n", dup);
	return (dup);
}

int	ground_rgb(char *str, int i, t_vars *cub)
{
	char	*dup;
	char	**rgb;
	int		hex;

	cub->count_l++;
	while (str[i] && !(ft_isdigit(str[i])))
		i++;
	dup = ft_strdup(&str[i]);
	rgb = ft_split(dup, ',');
	free(dup);
	hex = rgb_to_hex(rgb);
//	free(rgb[0]);
//	free(rgb[1]);
//	free(rgb[2]);
//	free(rgb);
	// printf("%s\n", dup);
	return (hex);
}

int	sky_rgb(char *str, int i, t_vars *cub)
{
	char	*dup;
	char	**rgb;
	int		hex;

	cub->count_l++;
	while (str[i] && !(ft_isdigit(str[i])))
		i++;
	dup = ft_strdup(&str[i]);
	rgb = ft_split(dup, ',');
	free(dup);
	hex = rgb_to_hex(rgb);
//	free(rgb[0]);
//	free(rgb[1]);
//	free(rgb[2]);
//	free(rgb);
	// printf("%s\n", dup);
	return (hex);
}

int	sorting_data(char **map, t_vars *cub)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < 7 && (size_t)i < cub->size_map)
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
	cub->map = ft_split(tmp, '\n');
	free(tmp);
	close(fd);

	// affichage test

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
	new_map = malloc((cub->size_map + 2) * sizeof(char *));
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
}

int main(int ac, char **av)
{
	t_vars	cub;
	
	(void)ac;
	open_file(av, &cub);
	cub.count_l = 0;
	if (!(sorting_data(cub.map, &cub)))
	{
		// ft_putstr_fd("Error, too less informations\n", 1);
		// free_tab(cub.map);
		// return (0);
	}
	set_map(&cub);
	if (!ft_parsing(ac, av, &cub))
	{
		// ft_free_all(&cub);
		// return (0);
	}
	// ft_free_all(&cub);

/*----------------------------------------------------------*/

	//main de phabets

	t_game game;

//	game.posX = 7;
//	game.posY = 2;
	game.dirX = -1;
	game.dirY = 0;
	game.planeX = 0;
	game.planeY = 0.66;
	find_pos(&cub, &game);
	game.cub = &cub;

	game.mlx = mlx_init();
	game.texture = malloc(sizeof(int *) * 4);
	for (int i = 0; i < 4; i++)
	{
		game.texture[i] = malloc(sizeof(int) * (64 * 64));
		for (int j = 0; j < 64 * 64; j++)
		{
			game.texture[i][j] = 0;
		}
	}
	load_all_texture(&game);
	game.mlx_win = mlx_new_window(game.mlx, 640, 480, "Cub3d");
	//while(1)
	//{
		/*
		double oldDirX = game.dirX;
		game.dirX = game.dirX * cos(-100) - game.dirY * sin(-100);
		game.dirY = oldDirX * sin(-100) + game.dirY * cos(-100);
		double oldPlaneX = game.planeX;
		game.planeX = game.planeX * cos(-100) - game.planeY * sin(-100);
		game.planeY = oldPlaneX * sin(-100) + game.planeY * cos(-100);*/
//	}
//	mlx_loop_hook(game.mlx, raycasting, game);
	game.img.img = mlx_new_image(game.mlx, 640, 480);
	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.size_l, &game.img.endian);
	render_frame(game);
	mlx_hook(game.mlx_win, 2, 1L<<0, &player_move_press, &game);
	mlx_hook(game.mlx_win, 3, 1L<<1, &player_move_release, &game);
	mlx_loop_hook(game.mlx, &player_move, &game);
	mlx_loop(game.mlx);

/*----------------------------------------------------------*/
	
	ft_free_all(&cub);
	return (0);
}
