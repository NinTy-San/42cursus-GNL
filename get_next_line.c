#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *) s;
	if (!s)
		return (NULL);
	i = 0;
	while (i < n)
		ptr[i++] = c;
	return (ptr);
}

char	*read_and_store(int fd,char *store)
{
	char	*reader;
	int		res;

	reader = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if(!reader)
		return (NULL);
	res = 1;
	while (res > 0 && !ft_strchr(store, '\n'))
	{
		ft_memset(reader, 0, BUFFER_SIZE + 1);
		res = read(fd, reader, BUFFER_SIZE);
		if(res <= 0 && !reader[0])
		{
			free(reader);
			if (!store ||store[0] == 0)
				return(NULL);
			return (store);
		}
		reader[res] = '\0';
		if (res == 0)
			break;
		store = ft_strjoin(store, reader);
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
	// new_store = ft_strdup(store);
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	new_store = malloc(sizeof(char) * (len - i) +1);
	if (!new_store)
		return (NULL);
	j = 0;
	// i++;
	while (i < len)
	{
		new_store[j] = store[i];
		i++;
		j++;
	}
	new_store[j] = '\0';
	// free (store);
	// store = new_store;
	free(store);
	return (new_store);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char *tmp;
	char	*line;

	tmp = store;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
			return (NULL);
	tmp = read_and_store(fd, tmp);
	if (!tmp)
		return (NULL);
	line = get_current_line(tmp);
	if (!line)
		return (NULL);
	tmp = get_new_store(tmp);
	store = tmp;
	// free(tmp);

	// printf("store = %s", store);

	return(line);
}
