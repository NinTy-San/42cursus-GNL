#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return(len);
}

char	*ft_strchr(char *s, int c)
{
	int		i;

	if (!s)
		return(NULL);
	if (c == '\0')
		return ((char *) s + ft_strlen(s));
		// return(NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	size_t	lens1;
	size_t	lens2;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
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
	// free(s1);
	// s1 = ft_strdup(newstr);
	free(s1);
	return (newstr);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*sc;
	char		*dst;

	sc = src;
	dst = dest;
	while (n--)
		*dst++ = *sc++;
	return (dest);
}

char	*ft_strdup(char *s)
{
	char	*dest;
	size_t	slen;

	slen = ft_strlen((char *) s);
	dest = (char *)malloc(sizeof (char) * slen + 1);
	ft_memcpy(dest, s, slen);
	dest[slen] = '\0';
	return (dest);
}

