#include <api.h>

void	show_pokemons(struct mg_connection *c, struct mg_http_message *request)
{
	char	*json_response;
	int		status;

	json_response = read_row("pokemon", "id,name,type", NULL);
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
 	sprintf(statement, "id=%d",id);
	json_response = read_row("pokemon", "id,name,type", statement);
	if (json_response == NULL)
		status = mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when reading pokemon's table");
	else
	{
		status = mg_http_reply(c, HTTP_OK, "", "%s", json_response);
		free(json_response);
	}
	char	uri[255];
	sprintf(uri, "/pokemon/%d", id);
	add_log("GET", uri, status, request->head.ptr);
}

void	store_pokemon(struct mg_connection *c, struct mg_http_message *request)
{
	js_node		poke;
	char		*json;
	char		values[600];
	char		*type;
	char		*name;
	int			status;

	json = (char *) request->body.ptr;
	js_new_obj(json, &poke);
	if (js_get_value(poke.obj_value, "name") == 0 || js_get_value(poke.obj_value, "type") == 0)
		status = mg_http_reply(c, HTTP_BAD_REQUEST, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_BAD_REQUEST, "Pokemon's name and type is needed when creating  a pokemon.");
	else
	{
		name = js_get_value(poke.obj_value, "name")->string_value;
		type = js_get_value(poke.obj_value, "type")->string_value;
		sprintf(values, "'%s', '%s'", name, type);
		if (create_row("pokemon", "name,type", values))
			status = mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when creating pokemon");
		else
			status = mg_http_reply(c, HTTP_CREATED, "", "{\"status:\":\"%d\"}", HTTP_CREATED);
	}
	add_log("POST", "/pokemon", status, request->head.ptr);
}

void	get_new_attrs(js_node *poke, char *new_attrs)
{
	js_node	*name;
	js_node	*type;
	char	tmp[500];

	name = js_get_value(poke, "name");
	type = js_get_value(poke, "type");
	if (name)
		sprintf(new_attrs, "name = '%s'", name->string_value);
	if (type)
	{
		sprintf(tmp, "type = '%s'", type->string_value);
		if (name)
			strcat(new_attrs, ",");
		strcat(new_attrs, tmp);
	}
}

void	update_pokemon(struct mg_connection *c, struct mg_http_message *request)
{
	char		statement[600];
	js_node		poke;
	char		new_attrs[1024];
	char		*json_obj;
	int			id;
	int			status;

	bzero(new_attrs, 1024);
	id = atoi(&request->uri.ptr[9]);
 	sprintf(statement, "id=%d",id);
	js_new_obj((char *)request->body.ptr, &poke);
	get_new_attrs(poke.obj_value, new_attrs);
	if (update_row("pokemon", new_attrs, statement))
		status = mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when updating pokemon");
	else
		status = mg_http_reply(c, HTTP_OK, "", "{\"status:\":\"%d\"}", HTTP_OK);
	char	uri[255];
	sprintf(uri, "/pokemon/%d", id);
	add_log("PUT", uri, status, request->head.ptr);
}

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
		status = mg_http_reply(c, HTTP_OK, "", "{\"status:\":\"%d}", HTTP_OK);
	char	uri[255];
	sprintf(uri, "/pokemon/%d", id);
	add_log("DELETE", uri, status, request->head.ptr);
}
