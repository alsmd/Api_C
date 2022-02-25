#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;

//	@brief	Desloc logs and returs the item
t_log	*get_page()
{
	int		index;
	t_log	*begin;

	begin = logs;
	index = 0;
	while (index < sys.desloc)
	{
		begin = begin->next;
		index++;
	}
	return (begin);
}