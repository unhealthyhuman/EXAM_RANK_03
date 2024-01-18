#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *st_sto, char *buffer);
char	*ft_strchr(char *s, char c);

#endif
