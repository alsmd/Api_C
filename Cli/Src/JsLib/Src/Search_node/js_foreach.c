#include <js_lib.h>

/*
	@brief		execute func in each node of the array
	@param		array (a js_node that has the type JSON_ARRAY)
	@param		func (pass each array's node to this function)
*/
void	js_foreach(js_node *array, void (*func)(js_node *item))
{
	js_node	*begin;

	begin = array->array_value;
	while (begin)
	{
		func(begin);
		begin = begin->next;
	}
}

/*
	@brief		execute func in each node of the obj chain
*/
void	js_foreach_node(js_node *obj, void (*func)(js_node *item))
{
	while (obj)
	{
		if (obj->type == JSON_OBJ)
			js_foreach_node(obj->obj_value, func);
		else if (obj->type == JSON_ARRAY)
			js_foreach_node(obj->array_value, func);
		else
			func(obj);
		obj = obj->next;
	}
}
