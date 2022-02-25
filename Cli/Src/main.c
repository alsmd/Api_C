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
	write(1, "[Enter] to select a request\n", 29);
	write(1, "[Backspace] returns to Log Table\n", 34);
	write(1, "\"q\" to quit.\n", 14);
	write(1, RESET, 7);
}

void	update()
{
	int		cmd;
	while (1)
	{
		render();
		write(1, "[space] to open/close helper.\n", 31);
		if (helper)
		{   
			for (int i = 0; i < 27; i++)
				printf(" ");
			printf("%s%s\n", WHITE, "↓");
			print_helper();
		}
		cmd = getch();
		if (cmd == 'q')
			return ;
		check_event(cmd);
		clean_term();
	}
}

void	init()
{
	bzero(&sys, sizeof(t_sys));
	create_nodes();
	sys.item_per_table = 6;
	sys.cur_page = 1;
	sys.desloc = 1;
	sys.default_color = WHITE;
	sys.screen = "table";
	sys.qnt_page = get_qnt_page();
}

int	main(void)
{
	init();
	update();
	return (0);
}
