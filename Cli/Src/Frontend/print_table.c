#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;
extern int		helper;

void	print_table(void)
{
	int		r;
	int		index;
	t_log	*begin;

	header();
	begin = get_page();
	index = 0;
	while (begin && index < sys.item_per_table)
	{
		if (index == sys.cursor)
			sys.default_color = RED;
		else
			sys.default_color = WHITE;
		item(begin);
		begin = begin->next;
		index++;
	}
	while (index < sys.item_per_table)
	{
		printf("\n");
		index++;
	}
	printf("\n");
}

void	print_item(void)
{
	t_log	*item;

	item = sys.active_log;
	if (js_get_value(item->obj, "Host"))
		printf("%s\n", js_get_value(item->obj, "Host")->string_value);
	printf("%s\n", item->uri);
	printf("\n");
}
