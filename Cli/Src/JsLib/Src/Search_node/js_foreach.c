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
