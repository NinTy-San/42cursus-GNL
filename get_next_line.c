#include "get_next_line.h"

char	*read_and_store(int fd,char *store)
{
	char	*reader;
	// char	*tmp;
	int		res;

	reader = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if(!reader)
		return (NULL);
	res = 1;
	while (res > 0 && !ft_strchr(store, '\n'))
	{
		res = read(fd, reader, BUFFER_SIZE);
		if(res <= 0)
		{
			free(reader);
			return(NULL);
		}
		reader[res] = '\0';
		// printf("reader = %s\n", reader);
		if (res == 0)
			break;
		store = ft_strjoin(store, reader);
		// if (store[0])
			// free(store);
		// store = tmp;
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
	if (store[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i--;
	j = 0;
	while(j <= i)
	{
		line[j] = store[j];
		j++;
	}
	// line[i] = '\n';
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
	if(!(len - i))
		return(NULL);
	new_store = malloc(sizeof(char) * (len - i) +1);
	if (!new_store)
		return (NULL);
	j = 0;
	i++;
	while (i < len)
	{
		new_store[j] = store[i];
		i++;
		j++;
	}
	new_store[j] = '\0';
	// free (store);
	store = new_store;
	// free(new_store);
	return (store);
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	store = read_and_store(fd, store);
	if (!store)
		return (NULL);
	line = get_current_line(store);
	if (!line)
		return (NULL);
	store = get_new_store(store);
	if (!store)
		return (NULL);
	return(line);
}
