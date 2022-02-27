#include <api.h>

void	remove_pokemon(struct mg_connection *c, struct mg_http_message *request)
{
	char		statement[600];
	int			id;
	int			status;

	id = atoi(&request->uri.ptr[9]);
 	sprintf(statement, "id=%d",id);
	if (delete_row("pokemon", statement))
		status = mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when deleting pokemon");
	else
		status = mg_http_reply(c, HTTP_OK, "", "{\"status:\":%d}", HTTP_OK);
	char	uri[255];
	sprintf(uri, "/pokemon/%d", id);
	add_log("DELETE", uri, status, request->head.ptr);
}