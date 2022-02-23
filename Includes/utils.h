#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include <string.h>
char	**split(char const *s, char c);
char	*strjoin(char *s1, char *s2);
void	free_matriz(char **matriz);

#endif