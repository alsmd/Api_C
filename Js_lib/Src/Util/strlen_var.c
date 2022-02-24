#include <js_lib.h>

/*
	@brief		Returns the buffer's length assuming the parameter end as been the end of the string.
				Null is also considered as end of the string.
*/
int	strlen_var(char *buffer, char end)
{
	int	index;

	index = 0;
	while (buffer[index] && buffer[index] != end)
		index++;
	return (index);
}