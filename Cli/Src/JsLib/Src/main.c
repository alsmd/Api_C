#include <js_lib.h>

void	printf_array_items(js_node *item)
{
	if (item->type == JSON_STRING)
		printf("%s\n", item->string_value);
	if (item->type == JSON_INTEGER ||item->type == JSON_BOOL)
		printf("%d\n", item->int_value);
}

//Teste

int	main(void)
{
	js_node	obj;
	
	js_new_array("[1, 2, \"Hello there!\", 4, true, false]", &obj);
	js_foreach(&obj, printf_array_items);
	free(obj.array_value);
	return (0);
}
