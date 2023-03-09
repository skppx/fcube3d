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
	{
		game->dirX = -1;
		game->dirY = 0;
		game->planeX = 0;
		game->planeY = 0.66;
	}
	else if (cub->map[i][j] == 'E')
	{
		game->dirX = 0;
		game->dirY = 1;
		game->planeX = 0.66;
		game->planeY = 0;
	}
	else if (cub->map[i][j] == 'S')
	{
		game->dirX = 1;
		game->dirY = 0;
		game->planeX = 0;
		game->planeY = -0.66;
	}
	else if (cub->map[i][j] == 'W')
	{
		game->dirX = 0;
		game->dirY = -1;
		game->planeX = -0.66;
		game->planeY = 0;
	}
}

void	load_texture(t_game *game, int *texture, char *path, t_img *img)
{
	int y;
	int x;

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

void	verLine(t_game *info, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(info->mlx, info->mlx_win, x, y, color);
		y++;
	}
}

/*
void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y *data->line_length + x * (data->bits_pre_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_floor_cieling(int color, t_game *game)
{
	t_data img;

	img.img = mlx_new_image*/

void	ft_draw(t_game *game)
{
	int	y;
	int x;

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
	int		texY;
	int		color;
	double	step; 
	double	texPos;
	int		texX;
	double	wallX;
	int		drawEnd;
	int		lineHeight;
	int		drawStart;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		i;
	int		j;

	mlx_clear_window(game.mlx, game.mlx_win);
	i = 0;
	while (i < 480 / 2)
	{
		j = 0;
		while (j < 640)
		{
			game.buf[i][j] = game.cub->sky; // sky
			j++;
		}
		i++;
	}
	i = 480 / 2;
	while (i < 480)
	{
		j = 0;
		while (j < 640)
		{
			game.buf[i][j] = game.cub->ground;  // ground
			j++;
		}
		i++;
	}

	for(int x = 0; x < 640; x++)
	{
		game.cameraX = 2 * x / 640.0f - 1;
		game.rayDirX = game.dirX + game.planeX * game.cameraX;
		game.rayDirY = game.dirY + game.planeY * game.cameraX;
		game.mapX = (int)(game.posX);
		game.mapY = (int)(game.posY);
		game.deltaDistX = sqrt(1 + (game.rayDirY * game.rayDirY) / (game.rayDirX * game.rayDirX));
		game.deltaDistY = sqrt(1 + (game.rayDirX * game.rayDirX) / (game.rayDirY * game.rayDirY));
		hit = 0;
		if (game.rayDirX < 0)
		{
			stepX = -1;
			game.sideDistX = (game.posX - game.mapX) * game.deltaDistX;
		}
		else
		{
			stepX = 1;
			game.sideDistX = (game.mapX + 1.0 - game.posX) * game.deltaDistX;
		}
		if (game.rayDirY < 0)
		{
			stepY = -1;
			game.sideDistY = (game.posY - game.mapY) * game.deltaDistY;
		}
		else
		{
			stepY = 1;
			game.sideDistY = (game.mapY + 1.0 - game.posY) * game.deltaDistY;
		}
		while(hit == 0)
		{
			if(game.sideDistX < game.sideDistY)
			{
				game.sideDistX += game.deltaDistX;
				game.mapX += stepX;
				side = 0;
			}
			else
			{
				game.sideDistY += game.deltaDistY;
				game.mapY += stepY;
				side = 1;
			}
			if(game.cub->map[game.mapX][game.mapY] != '0')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (game.mapX - game.posX + (1 - stepX) / 2) / game.rayDirX;
		else
			perpWallDist = (game.mapY - game.posY + (1 - stepY) / 2) / game.rayDirY;

		lineHeight = (int)(480 / perpWallDist);
		drawStart = -lineHeight / 2 + 480 / 2;
		if(drawStart < 0) drawStart = 0;
		drawEnd = lineHeight / 2 + 480 / 2;
		if(drawEnd >= 480) drawEnd = 480 - 1;
		if (side == 0)
			wallX = game.posY + perpWallDist * game.rayDirY;
		else
			wallX = game.posX + perpWallDist * game.rayDirX;
		wallX -= floor(wallX);

		texX = (int)(wallX * 64.0f);
		if (side == 0 && game.rayDirX > 0)
			texX = 64 - texX - 1;
		if (side == 1 && game.rayDirY < 0)
			texX = 64 - texX - 1;

		step = 1.0 * 64 / lineHeight;
		texPos = (drawStart - 480 / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			texY = (int)texPos & (63);
			texPos += step;
			if (game.rayDirX < 0 && side == 0)
				color = game.texture[0][64 * texY + texX];
			else if (game.rayDirX > 0 && side == 0)
				color = game.texture[1][64 * texY + texX];
			else if (side == 1 && game.rayDirY < 0)
				color = game.texture[2][64 * texY + texX];
			else
				color = game.texture[3][64 * texY + texX];
			game.buf[y][x] = color;
			game.re_buf = 1;
		}
	}
	ft_draw(&game);
}

int player_move_press(int keycode, t_game *game)
{

	if (keycode == 65307)
		exit(0);
	if (keycode == 119)
		game->forward = 1;
	else if (keycode == 115)
		game->backward = 1;
	if (keycode == 100)
		game->s_right = 1;
	else if (keycode == 97)
		game->s_left = 1;
	if (keycode == 65361)
		game->r_right = 1;
	else if (keycode == 65363)
		game->r_left = 1;
	return (0);
}

int player_move_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->forward = 0;
	else if (keycode == 115)
		game->backward = 0;
	else if (keycode == 100)
		game->s_right = 0;
	else if (keycode == 97)
		game->s_left = 0;
	else if (keycode == 65361)
		game->r_right = 0;
	else if (keycode == 65363)
		game->r_left = 0;
	return (0);
}

int	player_move(t_game *game)
{
	double rotspeed = 0.019400f;
	if (game->forward)//forward W
	{
		if (game->cub->map[(int)(game->posX + (game->dirX / 50))][(int)(game->posY + (game->dirY / 50))] == '0')
		{
			game->posX += (game->dirX / 50);
			game->posY += (game->dirY / 50);
		}
		render_frame(*game);
	}
	if (game->r_right)//<- rotate right
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(rotspeed) - game->dirY * sin(rotspeed);
		game->dirY = oldDirX * sin(rotspeed) + game->dirY * cos(rotspeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(rotspeed) - game->planeY * sin(rotspeed);
		game->planeY = oldPlaneX * sin(rotspeed) + game->planeY * cos(rotspeed);
		render_frame(*game);
	}

	if (game->backward)//backward S
	{
		if (game->cub->map[(int)(game->posX - (game->dirX / 50))][(int)(game->posY - (game->dirY / 50))] == '0')
		{
			game->posX -= (game->dirX / 50);
			game->posY -= (game->dirY / 50);
		}
		render_frame(*game);
	}
	if (game->s_right)//right D
	{
		if (game->cub->map[(int)(game->posX + (game->dirY / 50))][(int)(game->posY - (game->dirX / 50))] == '0')
		{
			game->posX += (game->dirY / 50);
			game->posY -= (game->dirX / 50);
		}
		render_frame(*game);
	}
	
	if (game->s_left)//left D
	{
		if (game->cub->map[(int)(game->posX - (game->dirY / 50))][(int)(game->posY + (game->dirX / 50))] == '0')
		{
			game->posX -= (game->dirY / 50);
			game->posY += (game->dirX / 50);
		}
		render_frame(*game);
	}

	if (game->r_left)//-> rotate right
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(-rotspeed) - game->dirY * sin(-rotspeed);
		game->dirY = oldDirX * sin(-rotspeed) + game->dirY * cos(-rotspeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(-rotspeed) - game->planeY * sin(-rotspeed);
		game->planeY = oldPlaneX * sin(-rotspeed) + game->planeY * cos(-rotspeed);
		render_frame(*game);
	}

	return (0);
}
