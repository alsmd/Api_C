#Json Lib

## How to Compile

- make
- gcc main.c -I$(LIB_PATH)/Include -L$(LIB_PATH) -ljs


## Simple Use


### Converting json object and getting attributes:  

```
#include <js_lib.h>

void	print_item(js_node *item)
{
	if (item->type == JSON_STRING)
		printf("\t%s\n", item->string_value);
}

int	main(void)
{
	char		*json_string;
	js_node	obj;
	
	json_string = "{\"name\": \"flavio\", \"age\": 19, \"male\": true, \"address\": null, \"roles\": [\"Database\", \"Frontend\", \"Backend\"], \"about\": {\"country\": \"Brasil\", \"has_car\": true}}";
	//Creating new object
	js_new_obj(json_string, &obj);

	//Searching for a string attribute
	printf("obj.name: %s\n", js_get_value(obj.obj_value, "name")->string_value);

	//Searching for an int attribute
	printf("obj.age: %d\n", js_get_value(obj.obj_value, "age")->int_value);

	//Searching for a bool attribute
	printf("obj.male: %s\n", js_get_value(obj.obj_value, "male")->int_value ? "yes" : "no");

	//Searching for a null attribute
	printf("obj.address: %s\n", js_get_value(obj.obj_value, "address")->type ? js_get_value(obj.obj_value, "address")->string_value : "NULL");

	//Searching for a array attribute and printing each item
	printf("Roles: \n");
	js_foreach(js_get_value(obj.obj_value, "roles"), print_item);

	//Searching for a object attribute 
	js_node	*about_obj = js_get_value(obj.obj_value, "about");
	//Making a new search in this object
	printf("obj.about.has_car: %s\n", js_get_value(about_obj->obj_value, "has_car")->int_value ? "yes" : "no");
	printf("obj.about.country: %s\n", js_get_value(about_obj->obj_value, "country")->string_value);

	return
}

```  

### Converting json array and getting iterating into it

```
#include <js_lib.h>

void	printf_array_items(js_node *item)
{
	if (item->type == JSON_STRING)
		printf("%s\n", item->string_value);
	if (item->type == JSON_INTEGER ||item->type == JSON_BOOL)
		printf("%d\n", item->int_value);
}

int	main(void)
{
	js_node	obj;
	
	js_new_array("[1, 2, \"Hello there!\", 4, true, false]", &obj);
	js_foreach(&obj, printf_array_items);
	return (0);
}

```

## Core

```
typedef enum e_json_type
{
	JSON_NULL,
	JSON_OBJ,
	JSON_ARRAY,
	JSON_STRING,
	JSON_INTEGER,
	JSON_BOOL
}	js_type;

typedef struct js_node
{
	js_type				type; //A Json Type
	char				*key; // If this node is part of an object chain it will store the item's key
	char				*string_value; // If this node is a JSON_STRING TYPE it will stored its value
	int					int_value; // If this node is a JSON_INTEGER or JSON_BOOL it will store its value
	struct js_node		*obj_value; // If this node is a Object it will store the node chain of the object
	struct js_node		*array_value; // If this node is an Array it will store the node chain of the array
	struct js_node		*next; //Next Item of the chain
}	js_node;

```