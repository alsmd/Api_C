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
	write(1, "[space] to open/close helper.\n", 31);
	if (helper)
	{   
		for (int i = 0; i < 27; i++)
			printf(" ");
		printf("%s%s\n", WHITE, "↓");
		render_helper();
	}
}