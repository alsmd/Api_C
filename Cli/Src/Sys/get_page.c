#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;

//	@brief	Desloc logs and returs the item
t_log	*get_page(t_log *log)
{
	int		index;
	t_log	*begin;

	begin = log;
	index = 0;
	while (index < sys.desloc && begin)
	{
		begin = begin->next;
		index++;
	}
	return (begin);
}

//	@brief	Get active log
t_log	*get_active_log(t_log *log)
{
	int		index;
	t_log	*begin;

	begin = get_page(log);
	index = 0;
	while (begin && index < sys.item_per_table)
	{
		if (index == sys.cursor)
			return (begin);
		index++;
		begin = begin->next;
	}
	return (0);
}