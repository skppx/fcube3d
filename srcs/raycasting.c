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

void    find_pos(t_vars *cub, t_game *game)
{
    int    i;
    int    j;

    i = 0;
    while(cub->map[i])
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

void	load_texture(t_game *game, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(game->mlx, img->img);
}

void load_all_texture(t_game *game)
{
	t_img img;
	load_texture(game, game->texture[0], "texture/colorstone.xpm", &img);
	load_texture(game, game->texture[1], "texture/eagle.xpm", &img);
	load_texture(game, game->texture[2], "texture/greystone.xpm", &img);
	load_texture(game, game->texture[3], "texture/redbrick.xpm", &img);
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

void	ft_draw(t_game *game)
{
	for (int y = 0; y < 480; y++)
	{
		for (int x = 0; x < 640; x++)
		{
			game->img.data[y * 640 + x] = game->buf[y][x];
		}
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
}

void	render_frame(t_game game)
{
		mlx_clear_window(game.mlx, game.mlx_win);
		
		for (int i = 0; i < 480; i++)
		{
			for (int j = 0; j < 640; j++)
			{
				game.buf[i][j] = 0;
			}
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
			double perpWallDist;
			int stepX;
			int stepY;
			int	hit = 0;
			int side;
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
/*				printf("-------------------\n");
				printf("%i\n",hit);
				printf("%i\n",game.mapX);
				printf("%i\n",game.mapY);
				printf("%c\n",game.cub->map[game.mapX][game.mapY]);*/
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
//				printf("hit?");
				if(game.cub->map[game.mapX][game.mapY] != '0')
					hit = 1;
			}
//			printf("final : %c\n",game.cub->map[game.mapX][game.mapY]);
//			printf("------------\n");
			//fish eye effect
			/*
			if (side == 0)
				perpWallDist = (game.sideDistX - game.deltaDistX);
			else
				perpWallDist = (game.sideDistY - game.deltaDistY);
				*/
			if (side == 0)
				perpWallDist = (game.mapX - game.posX + (1 - stepX) / 2) / game.rayDirX;
			else
				perpWallDist = (game.mapY - game.posY + (1 - stepY) / 2) / game.rayDirY;

			int lineHeight = (int)(480 / perpWallDist);
			int drawStart = -lineHeight / 2 + 480 / 2;
			if(drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + 480 / 2;
			if(drawEnd >= 480) drawEnd = 480 - 1;
			/*int color;
			switch(worldMap[game.mapX][game.mapY])
			{
				case 1:  color = 255;	break;
				case 2:  color = 65535;  break;
				case 3:  color = 16711935; break;
				default: color = 100;	break;
			}
			if(side == 1) {color = color / 2;}
			verLine(&game, x, drawStart, drawEnd, color);*/

			//printf("%i\n", texNum);
			double wallX;
			if (side == 0)
				wallX = game.posY + perpWallDist * game.rayDirY;
			else
				wallX = game.posX + perpWallDist * game.rayDirX;
			wallX -= floor(wallX);

			int texX = (int)(wallX * 64.0f);
			if (side == 0 && game.rayDirX > 0)
				texX = 64 - texX - 1;
			if (side == 1 && game.rayDirX < 0)
				texX = 64 - texX - 1;

			double step = 1.0 * 64 / lineHeight;
			double texPos = (drawStart - 480 / 2 + lineHeight / 2) * step;
			for (int y = drawStart; y < drawEnd; y++)
			{
				int texY = (int)texPos & (63);
				texPos += step;
				/*printf("oui%i\n", texY);
				printf("%i\n", texX);
				printf("%i\n", texNum);
				printf("%i\n", game.texture[1][2]);*/
				int color = game.texture[1][64 * texY + texX];
				if (side == 1)
					color = (color >> 1) & 8355711;
				game.buf[y][x] = color;
				game.re_buf = 1;
			}
		}
		ft_draw(&game);
}

int	player_move(int keycode, t_game *game)
{
	double rotspeed = 0.059400f;

	if (keycode == 65307)
		exit(0);
	else if (keycode == 119)//forward W
	{
		game->posX += (game->dirX / 10);
		game->posY += (game->dirY / 10);
		render_frame(*game);
	}
	else if (keycode == 65361)//<- rotate right
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(rotspeed) - game->dirY * sin(rotspeed);
		game->dirY = oldDirX * sin(rotspeed) + game->dirY * cos(rotspeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(rotspeed) - game->planeY * sin(rotspeed);
		game->planeY = oldPlaneX * sin(rotspeed) + game->planeY * cos(rotspeed);
		render_frame(*game);
	}

	else if (keycode == 115)//backward S
	{
		game->posX -= (game->dirX / 10);
		game->posY -= (game->dirY / 10);
		render_frame(*game);
	}
	else if (keycode == 100)//right D
	{
		game->posX += (game->dirY / 10);
		game->posY -= (game->dirX / 10);
		render_frame(*game);
	}
	
	else if (keycode == 97)//left D
	{
		game->posX -= (game->dirY / 10);
		game->posY += (game->dirX / 10);
		render_frame(*game);
	}

	else if (keycode == 65363)//-> rotate right
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
