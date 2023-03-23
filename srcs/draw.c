#include "cub3d.h"

void	draw_sky_floor(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 480 / 2)
	{
		j = 0;
		while (j < 640)
		{
			game->buf[i][j] = game->cub->sky;
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
			game->buf[i][j] = game->cub->ground;
			j++;
		}
		i++;
	}
}
