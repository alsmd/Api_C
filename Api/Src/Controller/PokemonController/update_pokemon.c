#include <api.h>

int	get_new_attrs(js_node *poke, char *new_attrs)
{
	js_node	*name;
	js_node	*type;
	js_node	*gen;
	char	tmp[1024];

	name = js_get_value(poke, "name");
	type = js_get_value(poke, "type");
	gen = js_get_value(poke, "gen");
	if (!name && !type && !gen)
		return (1);
	if (name)
		sprintf(new_attrs, "name = '%s'", name->string_value);
	if (type)
	{
		sprintf(tmp, "type = '%s'", type->string_value);
		if (name)
			strcat(new_attrs, ",");
		strcat(new_attrs, tmp);
	}
	if (gen)
	{
		sprintf(tmp, "gen = '%d'", gen->int_value);
		if (type || name)
			strcat(new_attrs, ",");
		strcat(new_attrs, tmp);
	}
	return (0);
}

void	update_pokemon(struct mg_connection *c, struct mg_http_message *request)
{
	char		statement[600];
	js_node		poke;
	char		new_attrs[1024];
	int			id;
	int			status;

	bzero(new_attrs, 1024);
	id = atoi(&request->uri.ptr[9]);
 	sprintf(statement, "id=%d",id);
	if (js_new_obj((char *)request->body.ptr, &poke) == 0)
		status = mg_http_reply(c, HTTP_BAD_REQUEST, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_BAD_REQUEST, "Wrong json format!");
	else
	{
		if (get_new_attrs(poke.obj_value, new_attrs) || update_row("pokemon", new_attrs, statement))
			status = mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when updating pokemon");
		else
			status = mg_http_reply(c, HTTP_OK, "", "{\"status:\":\"%d\"}", HTTP_OK);
		js_clean_obj(poke.obj_value);
	}
	char	uri[255];
	sprintf(uri, "/pokemon/%d", id);
	add_log("PUT", uri, status, request->head.ptr);
}
