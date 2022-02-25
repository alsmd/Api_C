#include <cli.h>

extern t_log	*logs;
extern t_size	sizes;
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

	r = printf("| %sMethod%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
	fill(r, sizes.method + 5);
	r = printf("| %sUri%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
	fill(r, sizes.uri + 3);
	r = printf("| %sStatus%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
	fill(r, 10);
	r = printf("| %sTime%s", CYAN, RESET) - strlen(CYAN) - strlen(RESET);
	fill(r, sizes.time + 4);
	printf("|\n");
}

void	item(t_log *item)
{
	int	r;

	r = printf("| %s%s%s", WHITE, item->method, RESET) - strlen(WHITE) - strlen(RESET);
	fill(r, sizes.method + 5);
	r = printf("| %s%s%s", WHITE, item->uri, RESET) - strlen(WHITE) - strlen(RESET);
	fill(r, sizes.uri + 3);
	r = printf("| %s%d%s", GREEN_LIGHT, item->status, RESET) - strlen(GREEN_LIGHT) - strlen(RESET);
	fill(r, 10);
	printf("| %s%s%s  |", WHITE, item->time, RESET) - strlen(WHITE) - strlen(RESET);
	printf("\n");
}

t_log	*get_page()
{
	int		index;
	t_log	*begin;

	begin = logs;
	index = 0;
	while (index < sizes.desloc)
	{
		begin = begin->next;
		index++;
	}
	return (begin);
}

void	print_table(void)
{
	int		r;
	int		index;
	t_log	*begin;

	header();
	begin = get_page();
	index = 0;
	while (begin && index < sizes.item_per_table)
	{
		item(begin);
		begin = begin->next;
		index++;
	}
	while (index < sizes.item_per_table)
	{
		printf("\n");
		index++;
	}
	printf("\n");
}

void	execute_action(int cmd)
{
	if ((cmd == 65 || cmd == 'w') && sizes.desloc > 0)
		sizes.desloc -= 1;
	if ((cmd == 66 || cmd == 's') && sizes.desloc < sizes.nodes)
		sizes.desloc += 1;
	if (cmd == ' ')
	{
		if (helper == 0)
			helper = 1;
		else
			helper = 0;
	}
}
