#include "cub3d.h"

void	set_render_frame(t_game *game, int x)
{
	game->cameraX = 2 * x / 640.0f - 1;
	game->rayDirX = game->dirX + game->planeX * game->cameraX;
	game->rayDirY = game->dirY + game->planeY * game->cameraX;
	game->mapX = (int)(game->posX);
	game->mapY = (int)(game->posY);
	game->deltaDistX = sqrt(1 + (game->rayDirY * game->rayDirY)
			/ (game->rayDirX * game->rayDirX));
	game->deltaDistY = sqrt(1 + (game->rayDirX * game->rayDirX)
			/ (game->rayDirY * game->rayDirY));
}

void	set2_render_frame(t_game *game, t_frame *frame)
{
	if (game->rayDirX < 0)
	{
		frame->stepx = -1;
		game->sideDistX = (game->posX - game->mapX) * game->deltaDistX;
	}
	else
	{
		frame->stepx = 1;
		game->sideDistX = (game->mapX + 1.0 - game->posX) * game->deltaDistX;
	}
	if (game->rayDirY < 0)
	{
		frame->stepy = -1;
		game->sideDistY = (game->posY - game->mapY) * game->deltaDistY;
	}
	else
	{
		frame->stepy = 1;
		game->sideDistY = (game->mapY + 1.0 - game->posY) * game->deltaDistY;
	}
}

void	side_hit(t_game *game, t_frame *frame)
{
	if (game->sideDistX < game->sideDistY)
	{
		game->sideDistX += game->deltaDistX;
		game->mapX += frame->stepx;
		frame->side = 0;
	}
	else
	{
		game->sideDistY += game->deltaDistY;
		game->mapY += frame->stepy;
		frame->side = 1;
	}
	if (game->cub->map[game->mapX][game->mapY] == '1')
		frame->hit = 1;
}
	
void	set3_render_frame(t_game *game, t_frame *frame)
{
	frame->lineheight = (int)(480 / frame->perpwalldist);
	frame->drawstart = -frame->lineheight / 2 + 480 / 2;
	if (frame->drawstart < 0)
		frame->drawstart = 0;
	frame->drawend = frame->lineheight / 2 + 480 / 2;
	if (frame->drawend >= 480)
		frame->drawend = 480 - 1;
	if (frame->side == 0)
		frame->wallx = game->posY + frame->perpwalldist * game->rayDirY;
	else
		frame->wallx = game->posX + frame->perpwalldist * game->rayDirX;
	frame->wallx -= floor(frame->wallx);
	frame->texx = (int)(frame->wallx * 64.0f);
	if (frame->side == 0 && game->rayDirX > 0)
		frame->texx = 64 - frame->texx - 1;
	if (frame->side == 1 && game->rayDirY < 0)
		frame->texx = 64 - frame->texx - 1;
	frame->step = 1.0 * 64 / frame->lineheight;
	frame->texpos = (frame->drawstart - 480
			/ 2 + frame->lineheight / 2) * frame->step;
}

void	choose_texture(t_game *game, t_frame *frame, int x, int y)
{
	frame->texy = (int)frame->texpos & (63);
	frame->texpos += frame->step;
	if (game->rayDirX < 0 && frame->side == 0)
		frame->color = game->texture[0][64 * frame->texy + frame->texx];
	else if (game->rayDirX > 0 && frame->side == 0)
		frame->color = game->texture[1][64 * frame->texy + frame->texx];
	else if (frame->side == 1 && game->rayDirY < 0)
		frame->color = game->texture[2][64 * frame->texy + frame->texx];
	else
		frame->color = game->texture[3][64 * frame->texy + frame->texx];
	game->buf[y][x] = frame->color;
	game->re_buf = 1;
}

void	perp_wall_dist(t_game *game, t_frame *frame)
{
	if (frame->side == 0)
	{
		frame->perpwalldist = (game->mapX - game->posX + (1 - frame->stepx) / 2)
			/ game->rayDirX;
	}
	else
	{
		frame->perpwalldist = (game->mapY - game->posY + (1 - frame->stepy) / 2)
			/ game->rayDirY;
	}
}
