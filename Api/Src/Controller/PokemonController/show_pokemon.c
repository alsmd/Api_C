#include <api.h>

void	show_pokemons(struct mg_connection *c, struct mg_http_message *request)
{
	char	*json_response;
	int		status;

	json_response = read_row("pokemon", "id,name,type,gen", NULL);
	if (json_response == NULL)
		status = mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when reading pokemon's table");
	else
	{
		status = mg_http_reply(c, HTTP_OK, "", "%s", json_response);
		free(json_response);
	}
	add_log("GET", "/pokemon", status, request->head.ptr);
}

void	show_pokemon(struct mg_connection *c, struct mg_http_message *request)
{
	char	statement[600];
	char	*json_response;
	int		id;
	int		status;

	id = atoi(&request->uri.ptr[9]);
 	sprintf(statement, "id=%d", id);
	json_response = read_row("pokemon", "id,name,type,gen", statement);
	if (json_response == NULL)
		status = mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when reading pokemon's table");
	else
	{
		if (strcmp(json_response, "[]"))
			status = mg_http_reply(c, HTTP_OK, "", "%s", json_response);
		else
			status = mg_http_reply(c, HTTP_NOT_FOUND, "", "{\"status\": %d, \"message\": \"Pokemon not found!\"}", HTTP_NOT_FOUND);
		free(json_response);
	}
	char	uri[255];
	sprintf(uri, "/pokemon/%d", id);
	add_log("GET", uri, status, request->head.ptr);
}