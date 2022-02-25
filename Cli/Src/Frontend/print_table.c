#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;
extern int		helper;

void	render_table(void)
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

void	print_element(js_node *item)
{
	int	r;

	if (item->type == JSON_STRING)
	{
		r = printf("%s:", item->key ? item->key : "Null");
		while (r <= 30)
		{
			printf(" ");
			r++;
		}
		printf("%s\n", item->string_value);
	}
}

void	render_item(void)
{
	t_log	*item;

	item = sys.active_log;
	clean_term();
	js_foreach_node(item->obj, print_element);
	printf("\n\n");
}
