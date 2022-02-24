#include <js_lib.h>

/*
	@brief	Search inside the js_node for the attribute that has key.
	@param	obj (js_node that is the base of the search)
	@param	key (what attribute we want to find)
	@return	Returns a js_node that is the attribute found or 0 if not found.
*/
js_node	*js_get_value(js_node *obj, char *key)
{
	js_node	*begin;

	begin = obj;
	while (begin)
	{
		if (!strcmp(begin->key, key))
			return (begin);
		begin = begin->next;
	}
	return (0);
}