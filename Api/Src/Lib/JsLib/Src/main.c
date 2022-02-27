#include <js_lib.h>

void	printf_array_items(js_node *item)
{
	if (item->type == JSON_STRING)
		printf("%s\n", item->string_value);
	if (item->type == JSON_INTEGER ||item->type == JSON_BOOL)
		printf("%d\n", item->int_value);
}

//Teste
/*
{"name": "Joe", "age": null, } - Extra comma (,) in object
{"name": "Joe", , "age": null} - Extra comma (,) in object
{"name": "Joe", "age": null] - Closing bracket is wrong
{"name": "Joe", "age": } - Missing value in name value pair in object
{"name": "Joe", "age" } - Missing : after name in object
{{}} - Missing name in object
*/
int	main(void)
{
	js_node	obj;
	
	printf("%p\n", js_new_obj("{asdasdqasd}", &obj));
	return (0);
}
