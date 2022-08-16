#include "get_next_line.h"

char	*read_and_store(int fd,char *store)
{
	char	*reader;
	int		res;

	reader = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!reader)
		return (NULL);
	res = 1;
	while (res && !ft_strchr(store, '\n'))
	{
		res = read(fd, reader, BUFFER_SIZE);
		if(res == -1)
		{
			free(reader);
			return(NULL);
		}
		reader[BUFFER_SIZE + 1] = '\0';
		printf("reader = %s\n", reader);
		store = ft_strjoin(store, reader);
	}
	free(reader);
	return(store);
}

char	*get_current_line(char *store)
{

}

char	*get_next_line(int fd)
{
	static char	*store;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = read_and_store(fd, store);
	if (!store)
		return (NULL);
	// printf("s = %s\n", ft_strchr(store, '\n'));
	return(store);
}
