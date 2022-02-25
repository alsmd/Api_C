#include <cli.h>

t_log	*logs = 0;
t_size	sizes;
int		helper = 0;

void    clean_term(void)
{
    write(1, "\033[2J\033[1;1H", 11);
}

int	get_qnt_page()
{
	int	nodes = sizes.nodes;
	int	qnt = 1;
	
	while (nodes > sizes.item_per_table)
	{
		nodes -= sizes.item_per_table;
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

	bzero(&sizes, sizeof(t_size));
	create_nodes();
	sizes.item_per_table = 6;
	sizes.cur_page = 1;
	sizes.desloc = 1;
	sizes.qnt_page = get_qnt_page();
	while (1)
	{
		clean_term();
		print_table();
		write(1, "[space] to open/close helper.\n", 31);
		if (helper)
			print_helper();
		write(1, "[cmd]: ", 8);
		cmd = getch();
		printf("%d\n", cmd);
		execute_action(cmd);
		clean_term();
	}
	return (0);
}
