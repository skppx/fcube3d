#include "cub3d.h"

void	move_forward(t_game *game)
{
	if (game->cub->map[(int)(game->posX + (game->dirX / 50))]
			[(int)(game->posY + (game->dirY / 50))] != '1')
	{
		game->posX += (game->dirX / 50);
		game->posY += (game->dirY / 50);
	}
	render_frame(*game);
}

void	move_backward(t_game *game)
{
	if (game->cub->map[(int)(game->posX - (game->dirX / 50))]
			[(int)(game->posY - (game->dirY / 50))] != '1')
	{
		game->posX -= (game->dirX / 50);
		game->posY -= (game->dirY / 50);
	}
	render_frame(*game);
}

void	move_right(t_game *game)
{
	if (game->cub->map[(int)(game->posX + (game->dirY / 50))]
			[(int)(game->posY - (game->dirX / 50))] != '1')
	{
		game->posX += (game->dirY / 50);
		game->posY -= (game->dirX / 50);
	}
	render_frame(*game);
}

void	move_left(t_game *game)
{
	if (game->cub->map[(int)(game->posX - (game->dirY / 50))]
			[(int)(game->posY + (game->dirX / 50))] != '1')
	{
		game->posX -= (game->dirY / 50);
		game->posY += (game->dirX / 50);
	}
	render_frame(*game);
}

void	rotate_left(t_game *game)
{
	double	rotspeed;
	double	olddirx;
	double	oldplanex;

	rotspeed = 0.019400f;
	olddirx = game->dirX;
	game->dirX = game->dirX * cos(-rotspeed) - game->dirY * sin(-rotspeed);
	game->dirY = olddirx * sin(-rotspeed) + game->dirY * cos(-rotspeed);
	oldplanex = game->planeX;
	game->planeX = game->planeX * cos(-rotspeed) - game->planeY
		* sin(-rotspeed);
	game->planeY = oldplanex * sin(-rotspeed) + game->planeY
		* cos(-rotspeed);
	render_frame(*game);
}

void	rotate_right(t_game *game)
{
	double	rotspeed;
	double	olddirx;
	double	oldplanex;

	rotspeed = 0.019400f;
	olddirx = game->dirX;
	game->dirX = game->dirX * cos(rotspeed) - game->dirY * sin(rotspeed);
	game->dirY = olddirx * sin(rotspeed) + game->dirY * cos(rotspeed);
	oldplanex = game->planeX;
	game->planeX = game->planeX * cos(rotspeed) - game->planeY
		* sin(rotspeed);
	game->planeY = oldplanex * sin(rotspeed) + game->planeY
		* cos(rotspeed);
	render_frame(*game);
}
