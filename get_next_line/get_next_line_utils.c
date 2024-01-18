#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
		size_t i = 0;

		if (!s)
				return (0);
		while (s[i])
				i++;
		return (i);
}

char	*ft_strchr(char *s, char c)
{
		if (!s)
				return (NULL);
		while (*s)
		{
				if (*s == c)
						return ((char *)s);
				s++;
		}
		if (c == '\0')
				return ((char *)s);
		return (NULL);
}

char	*ft_strjoin(char *st_sto, char *buffer)
{
		char	*dest;
		int		i = -1;
		int		j = 0;

		if (!st_sto)
		{
				st_sto = malloc(sizeof(char));
				if (!st_sto)
						return (NULL);
				st_sto[0] = '\0';
		}
		dest = malloc((ft_strlen(st_sto) + ft_strlen(buffer) + 1) * sizeof(char));
		if (!dest)
				return (free(st_sto), NULL);
		while (st_sto[++i])
				dest[i] = st_sto[i];
		while (buffer[j])
				dest[i++] = buffer[j++];
		dest[ft_strlen(st_sto) + ft_strlen(buffer)] = '\0';
		free(st_sto);
		return (dest);
}
