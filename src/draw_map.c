#include <so_long.h>

static void	draw_item(t_game *game, char item, int pos_x, int pos_y, int width, int height)
{
	Color color;

	color = BACKGROUND_COLOR;
	if (item == '1')
		color = WALL_COLOR;
	else if (item == '0')
		color = BACKGROUND_COLOR;
	else if (item == 'P')
		color = PLAYER_COLOR;
	else if (item == 'C')
		color = COLLECTIBLE_COLOR;
	else if (item == 'E')
	{
		if (game->nbr_collectibles == 0)
			color = EXIT_COLOR;
	}

	if (item == 'C')
		DrawCircle(pos_x + SQUARE_SIZE/2, pos_y + SQUARE_SIZE/2, SQUARE_SIZE/2, color);
	else
		DrawRectangle(pos_x, pos_y, width, height, color);
	if (item == 'P')
	{
		int d = game->eye_width;
		DrawRectangle(pos_x + 10 + game->player_eye_left, pos_y + 7, 7 - d, 7, BLACK);
		DrawRectangle(pos_x + SQUARE_SIZE - 7 - 10 + game->player_eye_right, pos_y + 7, 7 - d, 7 , BLACK);
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j] != '\n')
			draw_item(game, game->map[i][j], j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);	
	}
}
