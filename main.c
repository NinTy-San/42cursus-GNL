#include "get_next_line.h"

int main()
{
	int		fd = open("files/nl", O_RDONLY);
	char	*line;

	int i = 0;
	while(i < 3)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	return 0;
}