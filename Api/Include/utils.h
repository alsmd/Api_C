#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

char	**split(char const *s, char c);
char	*strjoin(char *s1, char *s2);
void	free_matriz(char **matriz);
void    add_log(char *method, char *route, int status);

#endif