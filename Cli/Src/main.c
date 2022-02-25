#include <cli.h>

t_log	*logs = 0;
t_sys	sys;
int		helper = 0;

void    clean_term(void)
{
    write(1, "\033[2J\033[1;1H", 11);
}

int	get_qnt_page()
{
	int	nodes = sys.nodes;
	int	qnt = 1;
	
	while (nodes > sys.item_per_table)
	{
		nodes -= sys.item_per_table;
		qnt++;
	}
	return (qnt);
}

void	print_helper()
{
	write(1, YELLOW_LIGHT, 8);
	write(1, "\"w/s\" to scroll throught the table.\n", 37);
	write(1, "\"a\" to change the table\n", 37);
	write(1, RESET, 7);
}

int	main(void)
{
	int		cmd;

	bzero(&sys, sizeof(t_sys));
	create_nodes();
	sys.item_per_table = 6;
	sys.cur_page = 1;
	sys.desloc = 1;
	sys.default_color = WHITE;
	sys.qnt_page = get_qnt_page();
	while (1)
	{
		clean_term();
		print_table();
		write(1, "[space] to open/close helper.\n", 31);
		if (helper)
		{   
			for (int i = 0; i < 27; i++)
				printf(" ");
			printf("%s%s\n", WHITE, "↓");
			print_helper();
		}
		cmd = getch();
		printf("%d\n", cmd);
		check_event(cmd);
		clean_term();
	}
	return (0);
}
