#include "get_next_line.h"

int main()
{
	int		fd = open("text.txt", O_RDONLY);
	char	*line;

	int i = 0;
	while(i < 15)
	{
		line = get_next_line(fd);
		// if (!line)
		// 	break;
		printf("%s", line);
		free(line);
		line = 0;
		i++;
	}
	close(fd);
	return 0;
}
