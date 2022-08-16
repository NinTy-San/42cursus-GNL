#include "get_next_line.h"

int main()
{
	int		fd;
	char	*test;
	fd = open("text.txt", O_RDONLY);
	test = get_next_line(fd);
	printf("resultat = %s\n", test);
}
