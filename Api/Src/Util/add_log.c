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

static int	ft_strlen_var(char *buffer, int end)
{
	int	index;

	index = 0;
	while (buffer[index] && buffer[index] != end)
		index++;
	return (index);
}

static void	remove_body(char *header)
{
	int	index;

	index = 0;
	while (header[index])
	{
		if (!strncmp(&header[index], "\r\n\r\n", 4))
			header[index] = 0;
		index++;
	}
}

static void    print_header(char *header, FILE *file_log)
{
	char	**argv;
	int		index;

	remove_body(header);
	argv = split(header, '\n');
	free(header);
	index = 0;
	while (argv[index])
	{
		if (is_in(argv[index], ':'))
		{
			char	*key = strndup(argv[index], ft_strlen_var(argv[index], ':'));
			char	*value = strndup(&argv[index][ft_strlen_var(argv[index], ':') + 1], strlen(&argv[index][ft_strlen_var(argv[index], ':') + 1]));
			remove_char(key, '\n');
			remove_char(key, 13);
			change_char(key, '"', '\'');
			remove_char(value, '\n');
			remove_char(value, 13);
			change_char(value, '"', '\'');
			fprintf(file_log, "\"%s\": \"%s\", ", key ? key : "null", value ? value : "null");
			free(key);
			free(value);
		}
		index++;
	}
	free_matriz(argv);
}

void    add_log(char *method, char *route, int status, const char *header)
{
	time_t	curtime;
	char	*str_time;
	FILE	*file_log = fopen("/Logs/log", "a");

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
		print_header(strdup(header), file_log);
		fprintf(file_log, "\"status\": %d", status);
		fprintf(file_log, "}\n");
		fclose(file_log);
	}
}
