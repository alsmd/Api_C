#include <utils.h>

static int	is_in(char *buffer, int c)
{
	while (*buffer)
	{
		if (*buffer == c)
			return (1);
		buffer++;
	}
	return (0);
}

static void	remove_char(char *buffer, char c)
{
	if (!buffer)
		return ;
	while (*buffer)
	{
		if (*buffer == c)
		{
			*buffer = '\0';
			return ;
		}
		buffer++;
	}
}

static void	change_char(char *buffer, char c, char s)
{
	while (*buffer)
	{
		if (*buffer == c)
			*buffer = s;
		buffer++;
	}
}

void    print_header(const char *header, FILE *file_log)
{
	char	**argv;
	char	**key_value;
	int		index;

	argv = split(header, '\n');
	index = 0;
	while (argv[index])
	{
		if (is_in(argv[index], ':'))
		{
			key_value = split(argv[index], ':');
			remove_char(key_value[0], '\n');
			remove_char(key_value[0], 13);
			change_char(key_value[0], '"', '\'');
			change_char(key_value[0], '{', '\'');
			change_char(key_value[0], '}', '\'');
			change_char(key_value[0], ':', '\'');
			change_char(key_value[0], ',', '\'');
			remove_char(key_value[1], '\n');
			remove_char(key_value[1], 13);
			change_char(key_value[1], '"', '\'');
			change_char(key_value[1], '{', '\'');
			change_char(key_value[1], '}', '\'');
			change_char(key_value[1], ':', '\'');
			change_char(key_value[1], ',', '\'');
			fprintf(file_log, "\"%s\": \"%s\", ", key_value[0] ? key_value[0] : "null", key_value[1] ? key_value[1] : "null");
			free_matriz(key_value);
		}
		index++;
	}
	free_matriz(argv);
}

void    add_log(char *method, char *route, int status, const char *header)
{
	time_t	curtime;
	char	*str_time;
	FILE	*file_log = fopen("../Logs/log", "a");

	time(&curtime);
	if (file_log != NULL)
	{
		fprintf(file_log, "{");
		fprintf(file_log, "\"method\": \"%s\", ", method);
		fprintf(file_log, "\"uri\": \"%s\", ", route);
		str_time = strdup(ctime(&curtime));
		str_time[strlen(str_time) - 1] = '\0';
		fprintf(file_log, "\"time\": \"%s\", ", str_time);
		free(str_time);
		print_header(header, file_log);
		fprintf(file_log, "\"status\": %d", status);
		fprintf(file_log, "}\n");
		fclose(file_log);
	}
	
}