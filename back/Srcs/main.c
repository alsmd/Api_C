#include <api.h>

static void	handle_request(struct mg_connection *c, int event, void *event_data, void *fn_data)
{
	if (event == MG_EV_HTTP_MSG)
		router(c, (struct mg_http_message *) event_data);
}

int	main(void)
{
	struct mg_mgr	mongoose;

	mg_mgr_init(&mongoose);
	mg_http_listen(&mongoose, "http://localhost:8000", handle_request, &mongoose);
	while (true)
		mg_mgr_poll(&mongoose, 1000);
	mg_mgr_free(&mongoose); 
}
