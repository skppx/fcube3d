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

typedef struct s_frame
{
	int		texy;
	int		color;
	double	step;
	double	texpos;
	int		texx;
	double	wallx;
	int		drawend;
	int		lineheight;
	int		drawstart;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
}		t_frame;

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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		*bits_per_pixel;
	int		*line_length;
	int		endian;
}		t_data;

typedef	struct s_vars
{
	// textures
	char	*wall_N;
	char	*wall_S;
	char	*wall_E;
	char	*wall_W;
	int		ground;
	int		sky;
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

	int		s_right;
	int		s_left;
	int		forward;
	int		backward;
	int		r_right;
	int		r_left;

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
int		player_move(t_game *game);
int		player_move_press(int keycode, t_game *game);
int		player_move_release(int keycode, t_game *game);
void	find_pos(t_vars *cub, t_game *game);
int		rgb_to_hex(char **rgb);
void	get_pole(t_vars *cub, t_game *game);
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	move_backward(t_game *game);
void	move_forward(t_game *game);
void	set_north(t_game *game);
void	set_east(t_game *game);
void	set_south(t_game *game);
void	set_west(t_game *game);
void	draw_sky_floor(t_game *game);
void	set_render_frame(t_game *game, int x);
void	set2_render_frame(t_game *game, t_frame *frame);
void	side_hit(t_game *game, t_frame *frame);
void	set3_render_frame(t_game *game, t_frame *frame);
void	choose_texture(t_game *game, t_frame *frame, int x, int y);
void	perp_wall_dist(t_game *game, t_frame *frame);

#endif
