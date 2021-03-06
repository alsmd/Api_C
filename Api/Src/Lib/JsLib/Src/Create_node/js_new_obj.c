#include <js_lib.h>

static char	*free_obj(js_node *obj)
{
	js_clean_obj(obj);
	return (0);
}

/*
	@brief		Receive a string json and convert to a js_node, you can use search function in this obj to get the attributes
	@param		json (json string that will be the base for the new js_node, it has to point to "{")
	@param		obj (a js_node where the new obj will be store.)
	@return		Returns a (char *) pointing to where this object ends inside the string json passed as parameter
*/
char	*js_new_obj(char *json, js_node *obj)
{
	js_node	*begin;

	bzero(obj, sizeof(obj));
	obj->type = JSON_OBJ;
	obj->obj_value = calloc(1, sizeof(js_node));
	begin = obj->obj_value;
	json = jump_whitespace(json);
	if (*json != '{')
		return (free_obj(obj->obj_value));
	json += 1;
	json = jump_whitespace(json);
	if (json[0] == '}')
		return (free_obj(obj->obj_value));
	while (*json != '}')
	{
		json = jump_whitespace(json);
		if (*json == '}')
			break ;
		if (*json == ',')
		{
			json++;
			json = jump_whitespace(json);
			if (*json != '"')
				return (free_obj(obj->obj_value));
			begin->next = calloc(1, sizeof(js_node));
			begin = begin->next;
			json = js_new_obj_attr(json, begin);
			if (json == 0)
				return (free_obj(obj->obj_value));
		}
		else if (*json == '"')
		{
			json = js_new_obj_attr(json, begin);
			if (json == 0)
				return (free_obj(obj->obj_value));
		}
		else
			return (free_obj(obj->obj_value));
	}
	json++;
	return (json);
}

char	*js_clean_obj(js_node *obj)
{
	js_node	*tmp;
	while (obj)
	{
		if (obj->type == JSON_STRING)
			free(obj->string_value);
		if (obj->type == JSON_ARRAY)
			js_clean_array(obj->array_value);
		if (obj->type == JSON_OBJ)
			js_clean_obj(obj->obj_value);
		if (obj->key)
			free(obj->key);
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
}
