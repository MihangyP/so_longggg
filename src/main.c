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

void	move(t_game *game, t_point player_position, char c)
{
	int	new_y = player_position.y;
	int new_x = player_position.x;
	static int pos_e_x;
	static int pos_e_y;

	if (c == 't')
		new_y = player_position.y - 1;
	else if (c == 'b')
		new_y = player_position.y + 1;
	else if (c == 'l')
		new_x = player_position.x - 1;
	else if (c == 'r')
		new_x = player_position.x + 1;

	if (game->map[new_y][new_x] != '1')
	{
		if (game->map[new_y][new_x] == 'C')
		{
			(game->nbr_collectibles)--;
			(game->score)++;
		}
		if (game->map[new_y][new_x] == 'E' && game->nbr_collectibles == 0)
			exit(0);
		if (game->map[new_y][new_x] == 'E' && game->nbr_collectibles != 0)
		{
			pos_e_x = new_x;
			pos_e_y = new_y;
		}
		if (pos_e_x && pos_e_y)
			game->map[pos_e_y][pos_e_x] = 'E';
		game->map[player_position.y][player_position.x] = '0';
		game->map[new_y][new_x] = 'P';
		if (c == 'l' && (!game->player_eye_left || !game->player_eye_right || game->player_eye_left == 5))
		{
			game->player_eye_left -= 5;
			game->player_eye_right -= 5;
			if (!game->player_eye_left)
				game->eye_width = 0;
			else
				game->eye_width = 3;
		}
		else if (c == 'r' && (!game->player_eye_left || !game->player_eye_right || game->player_eye_left == -5))
		{
			game->player_eye_left += 5;
			game->player_eye_right += 5;
			if (!game->player_eye_left)
				game->eye_width = 0;
			else
				game->eye_width = 3;
		}
		(game->move_counter)++;
		ft_printf("move: %d\n", game->move_counter);
	}
}

void	update_frame(t_game *game)
{
	t_point player_position;
	player_position = get_player_position(game->map);
	if (IsKeyPressed(KEY_W)) move(game, player_position, 't');
	if (IsKeyPressed(KEY_S)) move(game, player_position, 'b');
	if (IsKeyPressed(KEY_A)) move(game, player_position, 'l');
	if (IsKeyPressed(KEY_D)) move(game, player_position, 'r');
		
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);
	draw_map(game);
	// Stat
	{
		DrawRectangle(GetScreenWidth() - 170, 10, 150, 70, Fade(RED, .5f));
		DrawRectangleLines(GetScreenWidth() - 170, 10, 150, 70, RED);
		if (IsFontReady(game->font))
		{
			DrawTextEx(game->font, "Score", (Vector2){ GetScreenWidth() - 120, 20}, 30.0, 1.0, WHITE);
			DrawTextEx(game->font, ft_itoa(game->score), (Vector2){GetScreenWidth() - 100, 50}, 25, 1.0, WHITE);
		}
	}
	EndDrawing();
}

size_t	count_collectibles(char **map)
{
	size_t	counter;
	int		i;
	int		j;

	counter = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] != '\n')
		{
			if (map[i][j] == 'C')
				++counter;
		}
	}
	return (counter);
}

void	init_data(t_game *game, Font jbm)
{
	game->move_counter = 0;
	game->nbr_collectibles = count_collectibles(game->map);
	game->player_eye_left = 0;
	game->player_eye_right = 0;
	game->eye_width = 0;
	game->score = 0;
	game->font = jbm;
}

int main(int ac, char **av)
{
	t_game	game;
	size_t	window_width;
	size_t	window_height;

	handle_errors(ac, av);
	game.map = catch_map(av[1]);
	if (game.map == NULL)
		return (1);
	window_width = SQUARE_SIZE * calc_width(game.map);
	window_height = SQUARE_SIZE * calc_height(game.map);
	InitWindow(window_width, window_height, "So long");
	SetTargetFPS(60);
	Font jbm = LoadFont("JetBrainsMonoNerdFontMono-Bold.ttf");
	init_data(&game, jbm);
	while (!WindowShouldClose())
	{
		update_frame(&game);
	}
	UnloadFont(jbm);
	CloseWindow();
	free_map(game.map);
	return (0);
}
