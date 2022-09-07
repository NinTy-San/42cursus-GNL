#include "get_next_line.h"

int main()
{
	int		fd = open("files/text", O_RDONLY);
	char	*line;

	int i = 0;
	while(i < 14)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	return 0;
}