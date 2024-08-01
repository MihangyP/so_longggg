#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <raylib.h>
#include "../libft/libft.h"

/* size of a square*/
#define SQUARE_SIZE 40

/* colors */
#define BACKGROUND_COLOR SKYBLUE
#define PLAYER_COLOR WHITE
#define COLLECTIBLE_COLOR RED
#define WALL_COLOR BLACK
#define EXIT_COLOR GOLD

/* point */
typedef struct
{
	int	x;
	int	y;
}	t_point;

typedef struct
{
	size_t	nbr_collectibles;
	size_t	move_counter;
	char	**map;
	int		player_eye_left;
	int		player_eye_right;
	int		eye_width;
	int		score;
	Font	font;
}	t_game;

/* errors */
void	handle_errors(int ac, char **av);

/*  map manip */
char	**catch_map(const char *file_name);
size_t	calc_width(char **map);
size_t	calc_height(char **map);

/* draw map in window*/
void	draw_map(t_game *game);

/* free memory */
void	free_map(char **map);

#endif
