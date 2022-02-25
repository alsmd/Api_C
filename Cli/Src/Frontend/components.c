#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;
extern int		helper;

void	fill(int r, int size)
{
	while (r < size)
	{
		printf(" ");
		r++;
	}
}

void	header(char *title, int id, int total_request, int method, int uri, int status, int time)
{
	int	r;

	printf("\t\t\t\t%s\n\n", title);
	if (id)
	{
		r = printf("| %sid%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
		fill(r, 10);
	}
	if (total_request)
	{
		r = printf("| %sTotal_request%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
		fill(r, 23);
	}
	if (method)
	{
		r = printf("| %sMethod%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
		fill(r, sys.method + 5);
	}
	if (uri)
	{
		r = printf("| %sUri%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
		fill(r, sys.uri + 3);
	}
	if (status)
	{
		r = printf("| %sStatus%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
		fill(r, 10);
	}
	if (time)
	{
		r = printf("| %sTime%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
		fill(r, sys.time + 4);
	}
	printf("|\n");
}

void	item(t_log *item, int id, int total_request, int method, int uri, int status, int time)
{
	int	r;

	if (id)
	{
		r = printf("| %s%d%s", sys.default_color, item->id, RESET) - strlen(sys.default_color) - strlen(RESET);
		fill(r, 10);
	}
	if (total_request)
	{
		r = printf("| %s%d%s", sys.default_color, item->total_request, RESET) - strlen(sys.default_color) - strlen(RESET);
		fill(r, 23);
	}
	if (method)
	{
		r = printf("| %s%s%s", sys.default_color, item->method, RESET) - strlen(sys.default_color) - strlen(RESET);
		fill(r, sys.method + 5);
	}
	if (uri)
	{
		r = printf("| %s%s%s", sys.default_color, item->uri, RESET) - strlen(sys.default_color) - strlen(RESET);
		fill(r, sys.uri + 3);
	}
	if (status)
	{
		r = printf("| %s%d%s", sys.default_color, item->status, RESET) - strlen(sys.default_color) - strlen(RESET);
		fill(r, 10);
	}
	if (time)
		printf("| %s%s%s  ", sys.default_color, item->time, RESET);
	printf("|\n");
}

void    clean_term(void)
{
	write(1, "\033[2J\033[1;1H", 11);
}