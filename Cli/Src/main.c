#include <cli.h>

t_log	*logs = 0;
t_sys	sys;
int		helper = 0;

void	reset_sys()
{
	sys.desloc = 0;
	sys.cursor = 0;
}

void	init()
{
	bzero(&sys, sizeof(t_sys));
	create_nodes();
	sys.item_per_table = 6;
	reset_sys();
	sys.default_color = WHITE;
	sys.screen = "table";
}

int	main(void)
{
	init();
	run();
	return (0);
}
