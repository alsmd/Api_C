#include <api.h>

void	show_pokemons(struct mg_connection *c, struct mg_http_message *request)
{
	char	*json_response;

	json_response = read_row("pokemon", "id,name,type", NULL);
	if (json_response == NULL)
		mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when reading pokemon's table");
	else
	{
		mg_http_reply(c, HTTP_OK, "", "%s", json_response);
		free(json_response);
	}
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
	{
		mg_http_reply(c, HTTP_OK, "", "%s", json_response);
		free(json_response);
	}
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
		else
			mg_http_reply(c, HTTP_CREATED, "", "{\"status:\":\"%d}", HTTP_CREATED);
		free(pokemon.name);
		free(pokemon.type);
	}
}

void	update_pokemon(struct mg_connection *c, struct mg_http_message *request)
{
	t_pokemon	pokemon;
	char		statement[600];
	char		new_attrs[600];
	char		*json_obj;
	int			id;

	id = atoi(&request->uri.ptr[9]);
 	sprintf(statement, "id=%d",id);
	json_obj = read_row("pokemon", "name,type", statement);
	convert_json_to_object(json_obj, 2, "name", &pokemon.name, "type", &pokemon.type);
	convert_json_to_object(request->body.ptr, 2, "name", &pokemon.name, "type", &pokemon.type);
 	sprintf(new_attrs, "name='%s',type='%s'", pokemon.name, pokemon.type);
	if (update_row("pokemon", new_attrs, statement))
		mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when updating pokemon");
	else
		mg_http_reply(c, HTTP_OK, "", "{\"status:\":\"%d}", HTTP_OK);
	free(json_obj);
	free(pokemon.name);
	free(pokemon.type);
}

void	remove_pokemon(struct mg_connection *c, struct mg_http_message *request)
{
	char		statement[600];
	int			id;

	id = atoi(&request->uri.ptr[9]);
 	sprintf(statement, "id=%d",id);
	if (delete_row("pokemon", statement))
		mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when deleting pokemon");
	else
		mg_http_reply(c, HTTP_OK, "", "{\"status:\":\"%d}", HTTP_OK);
}
