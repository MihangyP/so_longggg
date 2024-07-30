#include <so_long.h>

static void	draw_item(char item, int pos_x, int pos_y, int width, int height)
{
	Color color;

	if (item == '1')
		color = WALL_COLOR;
	else if (item == '0')
		color = BACKGROUND_COLOR;
	else if (item == 'P')
		color = PLAYER_COLOR;
	else if (item == 'C')
		color = COLLECTIBLE_COLOR;
	else if (item == 'E')
		color = EXIT_COLOR;

	if (item == 'C')
		DrawCircle(pos_x + SQUARE_SIZE/2, pos_y + SQUARE_SIZE/2, SQUARE_SIZE/2, color);
	else
		DrawRectangle(pos_x, pos_y, width, height, color);
}

void	draw_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] != '\n')
			draw_item(map[i][j], j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);	
	}
}

