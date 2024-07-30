#include <so_long.h>

size_t	calc_width(char **map)
{
	size_t	width;

	width = 0;
	while (map[0][width] != '\n')
		++width;
	return (width);
}

size_t	calc_height(char **map)
{
	size_t	height;

	height = 0;
	while (map[height])
		++height;
	return (height);
}

static size_t	count_map_lines(const char *file_path)
{
	int		fd;
	size_t	counter;
	char	buffer[1];

	fd = open(file_path, O_RDONLY);
	// TODO: check if open return an error
	counter = 0;
	while (read(fd, buffer, 1))
	{
		if (*buffer == '\n')
			++counter;
	}
	close(fd);
	// TODO: check if close return an error
	return (counter);
}

char	**catch_map(const char *file_path)
{
	char	**res;
	char	*s;
	int		fd;
	int		i;
	size_t	map_lines;

	map_lines = count_map_lines(file_path);
	res = malloc((map_lines + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	i = 0;
	while ((s = get_next_line(fd)))
	{
		res[i] = s;
		++i;
	}
	res[i] = NULL;
	free(s);
	close(fd);
	return (res);
}
