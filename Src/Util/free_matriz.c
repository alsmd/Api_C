#include <utils.h>

//	@brief	Free a multidimensional matriz that is NULL termineted
void	free_matriz(char **matriz)
{
	int	index;

	index = 0;
	while (matriz[index])
	{
		free(matriz[index]);
		index++;
	}
	free(matriz);
}