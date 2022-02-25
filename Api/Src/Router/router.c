#include <api.h>

void	router(struct mg_connection *c, struct mg_http_message *request)
{
	
	if (mg_http_match_uri(request, "/pokemon") && !strncmp(request->method.ptr, "GET", 3))
		show_pokemons(c, request);
	else if (mg_http_match_uri(request, "/pokemon/*") && !strncmp(request->method.ptr, "GET", 3))
		show_pokemon(c, request);
	else if (mg_http_match_uri(request, "/pokemon") && !strncmp(request->method.ptr, "POST", 4))
		store_pokemon(c, request);
	else if (mg_http_match_uri(request, "/pokemon/*") && !strncmp(request->method.ptr, "PUT", 3))
		update_pokemon(c, request);
	else if (mg_http_match_uri(request, "/pokemon/1") && !strncmp(request->method.ptr, "DELETE", 6))
		remove_pokemon(c, request);
	else
	{
		mg_http_reply(c, HTTP_NOT_FOUND, "", "{\"status\":\"%d\"}", HTTP_NOT_FOUND);

        char **matrix = split((char *)request->method.ptr, ' ');
        add_log(matrix[0], matrix[1], 404);
        free_matriz(matrix);
	}
}
