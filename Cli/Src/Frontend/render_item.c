#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;
extern int		helper;

void	render_table(t_log *log, char *title, int id, int total_request, int method, int uri, int status, int time)
{
	int		index;
	t_log	*begin;

	header(title, id, total_request, method, uri, status, time);
	begin = get_page(log);
	index = 0;
	while (begin && index < sys.item_per_table)
	{
		if (index == sys.cursor)
			sys.default_color = RED;
		else
			sys.default_color = WHITE;
		item(begin, id, total_request, method, uri, status, time);
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

	r = printf("%s:", item->key ? item->key : "Null");
	while (r <= 30)
	{
		printf(" ");
		r++;
	}
	if (item->type == JSON_STRING)
		printf("%s\n", item->string_value);
	else if (item->type == JSON_INTEGER)
		printf("%d\n", item->int_value);

}

void	render_item(void)
{
	t_log	*item;

	item = sys.active_log;
	clean_term();
	printf("\t\t%sRequest Information:%s\n", CYAN_LIGHT, RESET);
	printf("_______________________________________________________________\n\n");
	printf("id:                           %d\n", item->id);
	js_foreach_node(item->obj, print_element);
	printf("\n\n");
}
