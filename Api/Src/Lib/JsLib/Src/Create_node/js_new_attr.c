#include <js_lib.h>

char	*store_by_type(js_node *obj, char *json)
{
	if (*json == '"')
	{
		obj->type = JSON_STRING;
		obj->string_value = js_new_string(json);
		json++;
		while (*json != '"')
			json++;
		json++;
	}
	if (*json == '[')
		json = js_new_array(json, obj);
	else if (*json == '{')
		json = js_new_obj(json, obj);
	else if (!strncmp(json, "true", 4))
	{
		obj->type = JSON_BOOL;
		json += 4;
		obj->int_value = 1;
	}
	else if (!strncmp(json, "false", 5))
	{
		obj->type = JSON_BOOL;
		json += 5;
		obj->int_value = 0;
	}
	else if (!strncmp(json, "null", 4))
	{
		obj->type = JSON_NULL;
		obj->string_value = strdup("");
		json += 4;
	}
	else if (is_number(*json))
	{
		obj->type = JSON_INTEGER;
		obj->int_value = atoi(json);
		while (is_number(*json))
			json++;
	}
	return (json);
}

/*
	@brief		Create a new object type and store in js_node *obj
	@param		json  (json string pointing to a json's key: "name": "flavio").
				It has to point to the double quoutes of the key
*/
char	*js_new_obj_attr(char *json, js_node *obj)
{
	json++;
	obj->key = strndup(json, strlen_var(json, '"'));
	while (*json != ':')
		json++;
	json++;
	json = jump_whitespace(json);
	json = store_by_type(obj, json);
	return (json);
}

/*
	@brief	
	@param		json  (json string pointing to the value of the array).
				
*/
char	*js_new_array_attr(char *json, js_node *obj)
{
	json = store_by_type(obj, json);
	return (json);
}