#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

//@brief	Split s string in array having char c has delimiter
char	**split(char const *s, char c);

//@brief	Join string s1 and s1, string s1 is freed
char	*strjoin(char *s1, char *s2);

//@brief	Freed a multidimensional array that is null termineted
void	free_matriz(char **matriz);

//@brief	Add a new Log into the log file
void    add_log(char *method, char *route, int status, const char *header);
#endif