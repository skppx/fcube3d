#include "cub3d.h"

int	player_move_press(int keycode, t_game *game)
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

int	player_move_release(int keycode, t_game *game)
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
	if (game->forward)
		move_forward(game);
	if (game->r_right)
		rotate_right(game);
	if (game->backward)
		move_backward(game);
	if (game->s_right)
		move_right(game);
	if (game->s_left)
		move_left(game);
	if (game->r_left)
		rotate_left(game);
	return (0);
}
