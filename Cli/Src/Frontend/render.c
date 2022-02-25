#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;
extern int		helper;

void	render()
{
	clean_term();
	if (!strcmp(sys.screen, "table"))
		render_table();
	else if (!strcmp(sys.screen, "item"))
		render_item();
}