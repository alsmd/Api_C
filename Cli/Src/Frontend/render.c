#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;
extern int		helper;

void	render()
{
	if (!strcmp(sys.screen, "table"))
		print_table();
	else if (!strcmp(sys.screen, "item"))
		print_item();
}