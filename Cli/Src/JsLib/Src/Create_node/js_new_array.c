#include <js_lib.h>

/*
	@brief		Receive a string json and convert to a js_node, you can use js_get_value in this obj to get the attributes
	@param		json (json string that will be the base for the new js_node, it has to point to "[")
	@param		obj (a js_node where the new obj will be store.)
	@return		Returns a (char *) pointing to where this array ends inside the string json passed as parameter
*/
char	*js_new_array(char *json, js_node *obj)
{
	js_node	*begin;

	obj->array_value = calloc(1, sizeof(js_node));
	obj->type = JSON_ARRAY;
	begin = obj->array_value;
	json += 1;
	while (*json != ']')
	{
		json = jump_whitespace(json);
		if (*json == ']')
			break ;
		if (*json == ',')
		{
			json++;
			json = jump_whitespace(json);
			begin->next = calloc(1, sizeof(js_node));
			begin = begin->next;
			json = js_new_array_attr(json, begin);
		}
		else
			json = js_new_array_attr(json, begin);
	}
	json++;
	return (json);
}