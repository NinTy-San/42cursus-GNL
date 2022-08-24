#include "get_next_line.h"

int main()
{
	int		fd = open("files/nl", O_RDONLY);
	char	*line;

	int i = 0;
	while(i < 15)
	{
		line = get_next_line(fd);
		printf("%s", line);
		i++;
	}
	close(fd);
	return 0;
}