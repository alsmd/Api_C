#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;
extern int		helper;

void	render()
{
	
	clean_term();
	if (!strcmp(sys.screen, "table"))
		render_table(logs, "Total Requests", OFF, ON, ON, ON, OFF, OFF);
	else if (!strcmp(sys.screen, "table_item"))
		render_item();
	else if (!strcmp(sys.screen, "table_uri"))
		render_table(sys.selected_uri, "Same Request", ON, OFF, ON, ON, ON, ON);
	write(1, "[space] to open/close helper.\n", 31);
	if (helper)
	{   
		for (int i = 0; i < 27; i++)
			printf(" ");
		printf("%s%s\n", WHITE, "↓");
		render_helper();
	}
}