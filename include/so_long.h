#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../libft/libft.h"

/* errors */
void	handle_errors(int ac, char **av);

/* catch map */
char	**catch_map(const char *file_name);

#endif
