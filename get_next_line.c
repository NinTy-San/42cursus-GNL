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
		// printf("reader = %s\n", reader);
		store = ft_strjoin(store, reader);
		if (res == 0)
			return (NULL);
	}
	free(reader);
	return(store);
}

char	*get_current_line(char *store)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	j = 0;
	while(j <= i)
	{
		line[j] = store[j];
		j++;
	}
	line[i] = '\n';
	line[++i] = '\0';
	return(line);
}

char *get_new_store(char *store)
{
	char	*new_store;
	int		len;
	int		i;
	int		j;

	i = 0;
	len = ft_strlen(store);
	while (store[i] && store[i] != '\n')
		i++;
	new_store = malloc(sizeof(char) * (len - i) + 1);
	if (!new_store)
		return (NULL);
	j = 0;
	while (i < len)
		new_store[j++] = store[++i];
	new_store[j] = '\0';
	return (new_store);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char	*line;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = read_and_store(fd, store);
	if (!store)
		return (NULL);
	line = get_current_line(store);
	store = get_new_store(store);
	return(line);
}
