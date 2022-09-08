/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adohou <adohou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:33:08 by adohou            #+#    #+#             */
/*   Updated: 2022/09/08 17:09:17 by adohou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	int		i;

	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *) s + ft_strlen(s));
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		lens1;
	int		lens2;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	newstr = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (lens1--)
			*(newstr + j++) = *(s1 + i++);
	i = 0;
	while (lens2--)
		*(newstr + j++) = *(s2 + i++);
	*(newstr + j) = '\0';
	free(s1);
	return (newstr);
}
