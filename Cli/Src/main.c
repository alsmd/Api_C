#include <cli.h>

t_log	*logs = 0;
t_sys	sys;
int		helper = 0;

void	reset_sys()
{
	sys.desloc = 0;
	sys.cursor = 0;
}

void	init(int item_per_table)
{
	bzero(&sys, sizeof(t_sys));
	create_nodes();
	sys.item_per_table = item_per_table;
	if (sys.item_per_table == 0)
		sys.item_per_table = 3;
	reset_sys();
	sys.default_color = WHITE;
	sys.screen = "table";
}

int	main(int argc, char *argv[])
{
	init(atoi(argv[1]));
	run();
	return (0);
}
