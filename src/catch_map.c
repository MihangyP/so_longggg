#include <so_long.h>

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
	close(file_path);
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
	while (s = get_next_line(fd))
	{
		res[i] = s;
		++i;
		free(s);
	}
	close(fd);
	return (res);
}
