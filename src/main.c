#include <so_long.h>

t_point	get_player_position(char **map)
{
	t_point	pos = {0, 0};
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\n')
		{
			if (map[i][j] == 'P')
			{
				pos.x = j;
				pos.y = i;
				return (pos);
			}
			++j;
		}
		++i;
	}
	return (pos);
}

void	move_top(char **map, t_point player_position)
{
	int	new_y;

	new_y = player_position.y - 1;
	if (map[new_y][player_position.x] != '1')
	{
		map[player_position.y][player_position.x] = '0';
		map[new_y][player_position.x] = 'P';
	}
}

void	move_bottom(char **map, t_point	player_position)
{
	int	new_y;

	new_y = player_position.y + 1;
	if (map[new_y][player_position.x] != '1')
	{
		map[player_position.y][player_position.x] = '0';
		map[new_y][player_position.x] = 'P';
	}
}

void	move_left(char **map, t_point player_position)
{
	int	new_x;

	new_x = player_position.x - 1;
	if (map[player_position.y][new_x] != '1')
	{
		map[player_position.y][player_position.x] = '0';
		map[player_position.y][new_x] = 'P';
	}
}

void	move_right(char **map, t_point player_position)
{
	int	new_x;

	new_x = player_position.x + 1;
	if (map[player_position.y][new_x] != '1')
	{
		map[player_position.y][player_position.x] = '0';
		map[player_position.y][new_x] = 'P';
	}
}

void	update_frame(char **map)
{
	t_point player_position;
	player_position = get_player_position(map);
	if (IsKeyPressed(KEY_W)) move_top(map, player_position);
	if (IsKeyPressed(KEY_S)) move_bottom(map, player_position);
	if (IsKeyPressed(KEY_A)) move_left(map, player_position);
	if (IsKeyPressed(KEY_D)) move_right(map, player_position);
		
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);
	draw_map(map);
	EndDrawing();
}

int main(int ac, char **av)
{
	char	**map;
	size_t	window_width;
	size_t	window_height;

	handle_errors(ac, av);
	map = catch_map(av[1]);
	if (map == NULL)
		return (1);
	window_width = SQUARE_SIZE * calc_width(map);
	window_height = SQUARE_SIZE * calc_height(map);
	InitWindow(window_width, window_height, "So long");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		update_frame(map);
	}
	CloseWindow();
	free_map(map);
	return (0);
}
