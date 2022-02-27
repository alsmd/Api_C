#include <api.h>

int	missing_attr(js_node *poke)
{
	
	if (js_get_value(poke->obj_value, "name") == 0 || js_get_value(poke->obj_value, "type") == 0 || js_get_value(poke->obj_value, "gen") == 0)
		return (1);
	return (0);
}

void	store_pokemon(struct mg_connection *c, struct mg_http_message *request)
{
	js_node		poke;
	char		*json;
	char		values[600];
	int			status;

	json = (char *) request->body.ptr;
	if (js_new_obj(json, &poke) == 0 || missing_attr(&poke))
		status = mg_http_reply(c, HTTP_BAD_REQUEST, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_BAD_REQUEST, "Pokemon's name and type is needed when creating  a pokemon.");
	else
	{
		char	*name = js_get_value(poke.obj_value, "name")->string_value;
		char	*type = js_get_value(poke.obj_value, "type")->string_value;
		int		gen = js_get_value(poke.obj_value, "gen")->int_value;
		sprintf(values, "'%s', '%s', %d", name, type, gen);
		if (create_row("pokemon", "name,type,gen", values))
			status = mg_http_reply(c, HTTP_INTERNAL_ERROR, "", "{\"status:\":\"%d\",\"message\":\"%s\"}", HTTP_INTERNAL_ERROR, "Something went wrong when creating pokemon");
		else
			status = mg_http_reply(c, HTTP_CREATED, "", "{\"status:\":\"%d\"}", HTTP_CREATED);
		js_clean_obj(poke.obj_value);
	}
	add_log("POST", "/pokemon", status, request->head.ptr);
}