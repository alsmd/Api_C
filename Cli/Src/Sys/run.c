#include <cli.h>

extern t_log	*logs;

void	run()
{
	while (1)
	{
		render();
		update();
	}
}

void	clean_nodes(t_log *nodes)
{
	t_log	*tmp;

	while (nodes)
	{
		tmp = nodes;
		nodes = nodes->next;
		js_clean_obj(tmp->obj);
		clean_nodes(tmp->same_request->next);
		free(tmp->same_request);
		free(tmp);
	}
}

void	free_system()
{
	clean_nodes(logs);
}