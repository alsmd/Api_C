#include <api.h>

void	show_pokemons(struct mg_connection *c, struct mg_http_message *request)
{
	char	*json_response;

	json_response = read_row("pokemon", "id,name,type", NULL);
	if (json_response == NULL)
		mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when reading pokemon's table");
	else
		mg_http_reply(c, HTTP_OK, "", json_response);
}

void	show_pokemon(struct mg_connection *c, struct mg_http_message *request)
{
	char	statement[600];
	char	*json_response;
	int		id;

	id = atoi(&request->uri.ptr[9]);
 	sprintf(statement, "id=%d",id);
	json_response = read_row("pokemon", "id,name,type", statement);
	if (json_response == NULL)
		mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when reading pokemon's table");
	else
		mg_http_reply(c, HTTP_OK, "", json_response);
}

void	store_pokemon(struct mg_connection *c, struct mg_http_message *request)
{
	t_pokemon	pokemon;
	char		values[600];

	bzero(&pokemon, sizeof(pokemon));
	convert_json_to_object(request->body.ptr, 2, "name", &pokemon.name, "type", &pokemon.type);
	if (pokemon.name == 0 || pokemon.type == 0)
		mg_http_reply(c, 200, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_BAD_REQUEST, "Pokemon's name and type is needed when creating  a pokemon.");
	else
	{
		sprintf(values, "'%s', '%s'", pokemon.name, pokemon.type);
		if (create_row("pokemon", "name,type", values))
			mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when creating pokemon");
		mg_http_reply(c, HTTP_CREATED, "", "{\"status:\":\"%d}", HTTP_CREATED);
	}
}