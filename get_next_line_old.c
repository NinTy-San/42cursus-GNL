/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adohou <adohou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:32:54 by adohou            #+#    #+#             */
/*   Updated: 2022/09/07 21:41:21 by adohou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *reader)
{
	free(reader);
	if (!store || store[0] == 0)
	{
		free(store);
		return (NULL);
	}
	return (NULL);
}

static char	*read_and_store(int fd, char *store)
{
	char	*reader;
	int		res;

	reader = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!reader)
		return (NULL);
	if (!store)
	{
		store = (char *)malloc(sizeof(char) * 1);
		store[0] = '\0';
	}
	res = 1;
	while (res != 0 && !ft_strchr(store, '\n'))
	{
		ft_memset(reader, 0, BUFFER_SIZE + 1);
		res = read(fd, reader, BUFFER_SIZE);
		if (res <= 0 && !reader[0])
			return (ft_free(reader));
		reader[res] = '\0';
		if (res == 0)
			break ;
		store = ft_strjoin(store, reader);
	}
	free(reader);
	return (store);
}

static char	*get_current_line(char *store)
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
	while (j <= i)
	{
		line[j] = store[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*get_new_store(char *store)
{
	char	*new_store;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(store);
	// if (store[i] == '\n')
	// 	i++;
	// else
		while (store[i] && store[i] != '\n')
			i++;
	if (!store[i])
	{
		free(store);
		return (NULL);
	}
	new_store = malloc(sizeof(char) * (len - i + 1));
	if (!new_store)
		return (NULL);
	while (store[i])
		new_store[j++] = store[i++];
	new_store[j] = '\0';
	free(store);
	return (new_store);
}

char	*get_next_line(int fd)
{
	static char	*store;
	// char		*tmp;
	char		*line;

	// tmp = store;
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
	// free(tmp);
	return (line);
}
