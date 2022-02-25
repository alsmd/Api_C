#include <cli.h>

extern t_log	*logs;
extern t_sys	sys;
int				id_available;

t_log	*copy(t_log *l, js_node *obj)
{
	t_log	*cpy;

	cpy = calloc(1, sizeof(t_log));
	cpy->method = l->method;
	cpy->uri = l->uri;
	cpy->time = l->time;
	cpy->status = l->status;
	cpy->obj = obj;
	return (cpy);
}

void	init_log(t_log *log, char *buffer)
{
	js_node	obj;

	js_new_obj(buffer, &obj);
	log->id = id_available;
	log->method = js_get_value(obj.obj_value, "method")->string_value;
	log->uri = js_get_value(obj.obj_value, "uri")->string_value;
	log->time = js_get_value(obj.obj_value, "time")->string_value;
	log->status = js_get_value(obj.obj_value, "status")->int_value;
	log->same_request = copy(log, obj.obj_value);
	log->obj = obj.obj_value;
	log->total_request = 1;
}

static void	add_to_list(t_log *list, t_log *new)
{
	while (list->next)
		list = list->next;
	list->next = new;
}

void	add_node(char *buffer)
{
	t_log	*new_log;
	t_log	*begin;

	new_log = calloc(1, sizeof(t_log));
	sys.nodes += 1;
	init_log(new_log, buffer);
	begin = logs;
	if (logs == 0)
		logs = new_log;
	else
	{
		while (begin)
		{
			if (!strcmp(begin->method, new_log->method) && !strcmp(begin->uri, new_log->uri))
			{
				begin->total_request += 1;
				add_to_list(begin->same_request, new_log);
				break ;
			}
			if (!begin->next)
			{
				begin->next = new_log;
				break;
			}
			begin = begin->next;
		}
	}
}

void	set_sizes()
{
	t_log	*begin;

	begin = logs;
	while (begin)
	{
		if (strlen(begin->method) > sys.method)
			sys.method = strlen(begin->method);
		if (strlen(begin->time) > sys.time)
			sys.time = strlen(begin->time);
		if (strlen(begin->uri) > sys.uri)
			sys.uri = strlen(begin->uri);
		begin = begin->next;
	}
}

void	create_nodes()
{
	char	buffer[2048];
	FILE	*log = fopen("../Logs/log", "r");
	
	if (log)
	{
		while (fgets(buffer, 2048, log))
		{
			add_node(buffer);
			id_available += 1;
		}
	}
	fclose(log);
	set_sizes();
}