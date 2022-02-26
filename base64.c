#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

void	encode_chunk(char tri[3], char chunk_encoded[4])
{
	char	aux = -1;
	char	res = 0;

	chunk_encoded[0] = encoding_table[(tri[0] & (aux << 2)) >> 2];//sobra 2
	chunk_encoded[1] = encoding_table[((tri[0] & ~(aux << 2)) << 4) | ((tri[1] & (aux << 4)) >> 4)]; //sobra 4
	if (tri[1])
		chunk_encoded[2] = encoding_table[((tri[1] & ~(aux << 4)) << 2) | ((tri[2] & aux << 6) >> 6)];//sobra 6
	else
		chunk_encoded[2] = '=';
	if (tri[2])
		chunk_encoded[3] = encoding_table[(tri[2] & ~(aux << 6))];
	else
		chunk_encoded[3] = '=';
}

char	*encode_base64(char *str)
{
	char	*chunk_encoded;
	char	*encoded = strdup("");
	int		index = 0;

	unsigned char	c = -1;
	while (str[index])
	{
		chunk_encoded = calloc(4, sizeof(char));
		encode_chunk(&str[index], chunk_encoded);
		encoded = strjoin(encoded, chunk_encoded);
		if (str[index + 1] == '\0')
			index++;
		else if (str[index + 2] == '\0')
			index += 2;
		else
			index += 3;
	}
	return (encoded);
}
