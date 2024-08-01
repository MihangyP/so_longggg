#include <so_long.h>

static void	draw_item(t_game *game, char item, int pos_x, int pos_y, int width, int height)
{
	Color		color;

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
	{
		Rectangle	rec = {(float)(pos_x + 5), (float)(pos_y + 5), (float)(width - 10), (float)(height - 10)};
		DrawRectangle(pos_x + 5, pos_y + 5, width - 10, height - 10, color);
		DrawRectangleLinesEx(rec, 2, BLACK);
	}
	else if (item == 'E')
	{
		Rectangle	rec = {(float)(pos_x + 5), (float)(pos_y + 5), (float)(width - 10), (float)(height - 10)};
		DrawRectangle(pos_x + 5, pos_y + 5, width - 10, height - 10, color);
		if (game->nbr_collectibles == 0)
			DrawRectangleLinesEx(rec, 2, BLACK);

	}
	else if (item == 'P')
	{
		int d = game->eye_width;
		Rectangle	rec = {(float)pos_x, (float)pos_y, (float)width, (float)height};
		DrawRectangle(pos_x, pos_y, width, height, color);
		DrawRectangleLinesEx(rec, 2.0, BLACK);
		DrawRectangle(pos_x + 10 + game->player_eye_left, pos_y + 7, 7 - d, 7, BLACK);
		DrawRectangle(pos_x + SQUARE_SIZE - 7 - 10 + game->player_eye_right, pos_y + 7, 7 - d, 7 , BLACK);
	}
	else
		DrawRectangle(pos_x, pos_y, width, height, color);
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
