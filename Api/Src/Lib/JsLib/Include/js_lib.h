#ifndef JS_LIB_H
#define JS_LIB_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

typedef enum e_json_type
{
	JSON_NULL,
	JSON_OBJ,
	JSON_ARRAY,
	JSON_STRING,
	JSON_INTEGER,
	JSON_DOUBLE,
	JSON_BOOL
}	js_type;

typedef struct js_node
{
	js_type				type;
	char				*key;
	char				*string_value;
	int					int_value;
	struct js_node	*obj_value;
	struct js_node	*array_value;
	struct js_node	*next;
}	js_node;

/*
	@brief	Convert a json string into a json_obj and returns it.
*/
js_node	*js_convert_to_object(char *j);

/***************
 * 
 * 	CREATE NODES
 * 
****************/

char	*js_new_obj_attr(char *json, js_node *obj);
char	*js_new_array_attr(char *json, js_node *obj);
char	*js_new_obj(char *json, js_node *obj);
char	*js_new_array(char *json, js_node *obj);
char	*js_new_string(char *json);
char	*js_clean_array(js_node *obj);
char	*js_clean_obj(js_node *obj);

/***************
 * 
 * 	SEARCH NODES
 * 
****************/

js_node		*js_get_value(js_node *obj, char *key);
void		js_foreach(js_node *array, void (*func)(js_node *item));
void		js_foreach_node(js_node *obj, void (*func)(js_node *item));


/***************
 * 
 * 	UTILS
 * 
****************/

int		is_number(char c);
int		strlen_var(char *buffer, char end);
int		is_whitespace(char c);
char	*jump_whitespace(char *str);

#endif