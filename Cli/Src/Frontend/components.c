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

void	header()
{
	int	r;

	printf("\t\t\t\tLog Table\n\n");
	r = printf("| %sId%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
	fill(r, 8);
	r = printf("| %sMethod%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
	fill(r, sys.method + 5);
	r = printf("| %sUri%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
	fill(r, sys.uri + 3);
	r = printf("| %sStatus%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
	fill(r, 10);
	r = printf("| %sTime%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
	fill(r, sys.time + 4);
	printf("|\n");
}

void	item(t_log *item)
{
	int	r;

	r = printf("| %s%d%s", WHITE, item->id, RESET) - strlen(WHITE) - strlen(RESET);
	fill(r, 8);
	r = printf("| %s%s%s", sys.default_color, item->method, RESET) - strlen(sys.default_color) - strlen(RESET);
	fill(r, sys.method + 5);
	r = printf("| %s%s%s", sys.default_color, item->uri, RESET) - strlen(sys.default_color) - strlen(RESET);
	fill(r, sys.uri + 3);
	r = printf("| %s%d%s", sys.default_color, item->status, RESET) - strlen(sys.default_color) - strlen(RESET);
	fill(r, 10);
	printf("| %s%s%s  |", sys.default_color, item->time, RESET) - strlen(sys.default_color) - strlen(RESET);
	printf("\n");
}

void    clean_term(void)
{
	write(1, "\033[2J\033[1;1H", 11);
}