#include <so_long.h>

int main(int ac, char **av)
{
	char	**map;

	handle_errors(ac, av);
	map = catch_map(av[1]);
	return (0);
}
