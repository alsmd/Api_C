#include <cli.h>

extern int		helper;
extern t_log	*logs;
extern t_sys	sys;

void	update()
{
	int		cmd;

	cmd = getch();
	if (!strcmp(sys.screen, "table"))
		table_events(cmd, logs);
	else if (!strcmp(sys.screen, "table_uri"))
		table_uri_events(cmd, sys.selected_uri);
	else if (!strcmp(sys.screen, "table_item"))
		table_item_events(cmd);
	if (cmd == ' ')
	{
		if (helper == 0)
			helper = 1;
		else
			helper = 0;
	}
	if (cmd == 'q')
		exit(0);
}