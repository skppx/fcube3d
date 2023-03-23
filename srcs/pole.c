#include "cub3d.h"

void	set_north(t_game *game)
{
	game->dirX = -1;
	game->dirY = 0;
	game->planeX = 0;
	game->planeY = 0.66;
}

void	set_east(t_game *game)
{
	game->dirX = 0;
	game->dirY = 1;
	game->planeX = 0.66;
	game->planeY = 0;
}

void	set_south(t_game *game)
{
	game->dirX = 1;
	game->dirY = 0;
	game->planeX = 0;
	game->planeY = -0.66;
}

void	set_west(t_game *game)
{
	game->dirX = 0;
	game->dirY = -1;
	game->planeX = -0.66;
	game->planeY = 0;
}
