#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;
extern int		helper;

//	@brief	Check if there is more content to be display in the table
int	check_last(t_log *log)
{
	int		index;
	int		tmp;
	t_log	*begin;

	tmp = sys.desloc;
	sys.desloc += 1;
	begin = get_page(log);
	sys.desloc = tmp;
	index = 0;
	while (begin && index < sys.item_per_table)
	{
		begin = begin->next;
		index++;
	}
	if (index < sys.item_per_table)
		return (0);
	return (1);
}

void	move_events(int cmd, t_log *log)
{
	if ((cmd == 65 || cmd == 'w') && sys.desloc > 0 && sys.cursor == 0)
		sys.desloc -= 1;
	else if ((cmd == 65 || cmd == 'w') && sys.cursor > 0)
		sys.cursor -= 1;
	if ((cmd == 66 || cmd == 's') && check_last(log) && sys.cursor == sys.item_per_table - 1)
		sys.desloc += 1;
	else if ((cmd == 66 || cmd == 's') && sys.cursor < sys.item_per_table - 1)
		sys.cursor += 1;
}

void	table_events(int cmd, t_log *log)
{
	move_events(cmd, log);
	if (cmd == 10)
	{
		sys.selected_uri = get_active_log(logs)->same_request;
		reset_sys();
		system("clear");
		sys.screen = "table_uri";
	}
}

void	table_uri_events(int cmd, t_log *log)
{

	move_events(cmd, log);
	if (cmd == 10)
	{
		sys.active_log = get_active_log(sys.selected_uri);
		system("clear");
		sys.screen = "table_item";
	}
	if (cmd == 127)
	{
		system("clear");
		sys.screen = "table";
	}
}

void	table_item_events(int cmd)
{
	if (cmd == 127)
	{
		system("clear");
		sys.screen = "table_uri";
	}
}