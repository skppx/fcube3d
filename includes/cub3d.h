/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:09:52 by repinat           #+#    #+#             */
/*   Updated: 2023/03/02 17:11:45 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <../minilibx-linux/mlx.h>

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}		t_img;

typedef	struct s_vars
{
	// textures
	void	*wall_N;
	void	*wall_S;
	void	*wall_E;
	void	*wall_W;
	char	*ground;
	char	*sky;
	//map
	char	**map;
	size_t	size_map;
	int		count_l;
}	t_vars;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
	void	*win;

	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int	mapX;
	int mapY;
	int	buf[480][640];
	int	re_buf;
	int **texture;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	t_img	img;
	t_vars	*cub;
}		t_game;


int		ft_parsing(int ac, char **av, t_vars *cub);
void	free_tab(char **tab);
// int		map_size(char **av, t_vars *cub);
int		closed_map(char	**map, t_vars *cub);
void	ft_free_all(t_vars *cub);
void	load_texture(t_game *game, int *texture, char *path, t_img *img);
void	load_all_texture(t_game *game);
void	verLine(t_game *info, int x, int y1, int y2, int color);
void	ft_draw(t_game *game);
void	render_frame(t_game game);
int		player_move(int keycode, t_game *game);
void	find_pos(t_vars *cub, t_game *game);

#endif
