#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;
extern int		helper;

//	@brief	Check if there is more content to be display in the table
int	check_last()
{
	int		index;
	int		tmp;
	t_log	*begin;

	tmp = sys.desloc;
	sys.desloc += 1;
	begin = get_page();
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

void	table_events(int cmd)
{
	if ((cmd == 65 || cmd == 'w') && sys.desloc > 0 && sys.cursor == 0)
		sys.desloc -= 1;
	else if ((cmd == 65 || cmd == 'w') && sys.cursor > 0)
		sys.cursor -= 1;
	if ((cmd == 66 || cmd == 's') && check_last() && sys.cursor == sys.item_per_table - 1)
		sys.desloc += 1;
	else if ((cmd == 66 || cmd == 's') && sys.cursor < sys.item_per_table - 1)
		sys.cursor += 1;
}

void	check_event(int cmd)
{
	if (!strcmp(sys.screen, "table"))
		table_events(cmd);
	if (cmd == 10) //ENTER
	{
		sys.active_log = get_active_log();
		system("clear");
		sys.screen = "item";		
	}
	else if (cmd == 127)
	{
		if (strcmp(sys.screen, "table"))
		{
			sys.screen = "table";
			system("clear");
		}
	}
	if (cmd == ' ')
	{
		if (helper == 0)
			helper = 1;
		else
			helper = 0;
	}
}
