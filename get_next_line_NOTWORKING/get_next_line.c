#include "get_next_line.h"

static size_t	ft_strlen(char *s)
{
	size_t i = 0;

	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strchr(char *s, int c) //1er error "int c";
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

static char	*ft_strjoin(char *st_sto, char *buf)
{
	int	i = -1;
	int	j = 0;
	char	*dest;

	if (!st_sto)
	{
		st_sto = malloc(1 * sizeof(char));
		if (!st_sto)
			return (NULL);
		st_sto[0] = '\0';
	}
	if (!st_sto || !buf)
		return (NULL);
	dest = malloc((ft_strlen(st_sto) + ft_strlen(buf) + 1) * sizeof(char));
	if (!dest)
		return (free(st_sto), NULL);
	while (st_sto[++i])
		dest[i] = st_sto[i];
       while (buf[j])
		dest[i++] = buf[j++];
	dest[ft_strlen(st_sto) + ft_strlen(buf)] = '\0';
	if (dest[0] == '\0')
		return (free(st_sto), free(dest), NULL);
	free(st_sto);
	return (dest);	
}

static char	*fill_string(int fd, char *st_sto)
{
	char	*buffer;
	int	buffer_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer_read = 1;
	while (!(ft_strchr(st_sto, '\n')) && buffer_read != 0)
	{
		buffer_read = read(fd, buffer, BUFFER_SIZE);
		if (buffer_read < 0)
			return (free(st_sto), free(buffer), NULL);
		buffer[buffer_read] = '\0';
		if (buffer)
			st_sto = ft_strjoin(st_sto, buffer);
		if (!st_sto)
			return (free(st_sto), free(buffer), NULL);
	}
	free(buffer);
	return (st_sto);
}

static char	*clean_string(char *st_sto)
{
	char	*clean;
	int	i = 0;

	if (!st_sto[i] || !st_sto)
		return (NULL);
	while (st_sto[i] && st_sto[i] != '\n')
		i++;
	if (st_sto[i] == '\n')
		i++;
	clean = malloc((i + 1) * sizeof(char));
	if (!clean)
		return (NULL);
	i = -1;
	while (st_sto[++i] != '\n' && st_sto[i])
		clean[i] = st_sto[i];
	if (st_sto[i] == '\n')
		clean[i] = st_sto[i++];
	clean[i] = '\0';
	return (clean);
}

static char	*store_string(char *st_sto)
{
	char	*tmp;
	int	i = 0;
	int	j = 0;

	while (st_sto[i] != '\n' && st_sto[i])
		i++;
	if (!st_sto[i])
		return(free(st_sto), NULL);
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i++;
	while (st_sto[i])
		tmp[j++] = st_sto[i++];
	tmp[j] = '\0';
	if (tmp[0] == '\0')
		return (free(st_sto), free(tmp), NULL);
	free(st_sto);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*st_sto;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	st_sto = fill_string(fd, st_sto);
	if (!st_sto)
		return (free(st_sto), NULL);
	line = clean_string(st_sto);
	st_sto = store_string(st_sto);
	return (line);
}

int	main()
{
	int	fd = open("gg.txt", O_RDONLY);
	char	*line = get_next_line(fd);
		
	while (line != NULL)
	{
		printf("Line >> %s", line);
		free(line);
		line = get_next_line(fd);
	}
}
