/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: repinat <repinat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:56:44 by repinat           #+#    #+#             */
/*   Updated: 2023/03/02 17:17:42 by phabets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_pos(t_vars *cub, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'E'
					|| cub->map[i][j] == 'S' || cub->map[i][j] == 'W')
				break ;
			j++;
		}
		if (cub->map[i][j] == 'N' || cub->map[i][j] == 'E'
				|| cub->map[i][j] == 'S' || cub->map[i][j] == 'W')
			break ;
		i++;
	}
	game->posX = i;
	game->posY = j;
}

void	get_pole(t_vars *cub, t_game *game)
{
	int	i;
	int	j;

	i = game->posX;
	j = game->posY;
	if (cub->map[i][j] == 'N')
		set_north(game);
	else if (cub->map[i][j] == 'E')
		set_east(game);
	else if (cub->map[i][j] == 'S')
		set_south(game);
	else if (cub->map[i][j] == 'W')
		set_west(game);
}

void	load_texture(t_game *game, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->img_width,
			&img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l,
			&img->endian);
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, img->img);
}

void	load_all_texture(t_game *game)
{
	t_img	img;

	load_texture(game, game->texture[0], game->cub->wall_N, &img);
	load_texture(game, game->texture[1], game->cub->wall_S, &img);
	load_texture(game, game->texture[2], game->cub->wall_W, &img);
	load_texture(game, game->texture[3], game->cub->wall_E, &img);
}

void	ft_draw(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < 480)
	{
		x = 0;
		while (x < 640)
		{
			game->img.data[y * 640 + x] = game->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}

void	render_frame(t_game game)
{
	int		y;
	int		x;
	t_frame	frame;

	mlx_clear_window(game.mlx, game.mlx_win);
	draw_sky_floor(&game);
	x = 0;
	while (x < 640)
	{
		set_render_frame(&game, x);
		set2_render_frame(&game, &frame);
		frame.hit = 0;
		while (frame.hit == 0)
			side_hit(&game, &frame);
		perp_wall_dist(&game, &frame);
		set3_render_frame(&game, &frame);
		y = frame.drawstart;
		while (y < frame.drawend)
		{
			choose_texture(&game, &frame, x, y);
			y++;
		}
		x++;
	}
	ft_draw(&game);
}
