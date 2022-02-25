#include <js_lib.h>

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

char	*jump_whitespace(char *str)
{
	while (is_whitespace(*str))
		str++;
	return (str);
}