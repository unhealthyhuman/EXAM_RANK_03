#include "get_next_line.h"

char	*fill_string(int fd, char *st_sto)
{
		char	*buffer;
		int		buffer_read;

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

char	*clean_string(char	*st_sto)
{
		int	i = 0;
		char	*clean;

		if (!st_sto || !st_sto[i])
				return (NULL);
		while (st_sto[i] && st_sto[i] != '\n')
				i++;
		if (st_sto[i] == '\n')
				i++;
		clean = malloc((i + 1) * sizeof(char));
		if (!clean)
				return (NULL);
		i = -1;
		while (st_sto[++i] && st_sto[i] != '\n')
				clean[i] = st_sto[i];
		if (st_sto[i] == '\n')
		{
				clean[i] = st_sto[i];
				i++;
		}
		clean[i] = '\0';
		return (clean);
}

char	*store_string(char *st_sto)
{
		int i = 0;
		int j = 0;
		char *tmp;

		while (st_sto[i] != '\n' && st_sto[i])
				i++;
		if (!st_sto[i])
				return (free(st_sto), NULL);
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
		static char	*static_storage;

		if (fd < 0 || BUFFER_SIZE <= 0)
				return (NULL);
		static_storage = fill_string(fd, static_storage);
		if (!st_sto)
			return (free(static_storage), NULL);
		line = clean_string(static_storage);
		static_storage = store_string(static_storage);
		return (line);
}
