#ifndef JSON_H
#define JSON_H

typedef enum e_json_type
{
	JSON_NULL,
	JSON_OBJ,
	JSON_ARRAY,
	JSON_STRING,
	JSON_INTEGER,
	JSON_DOUBLE,
	JSON_BOOL
}	t_json_type;

typedef struct s_json_obj
{
	t_json_type			type;
	char				*key;
	char				*string_value;
	int					int_value;
	struct s_json_obj	*obj_value;
	struct s_json_obj	*next;
}	t_json_obj;

/*
	@brief	Convert a json string into a json_obj and returns it.
*/
t_json_obj	*js_convert_json_to_object(char *j);

/*
	@brief	Get a json_obj and search and returns the node that has the key passed as parameter. 
			If the node returned has the type JSON_OBJ it can be pass to a new js_get_value to a new search
*/
t_json_obj	*js_get_value(t_json_obj *obj, char *key);


char	*new_json_obj(char *json, t_json_obj *o);
char	*new_json_string(char *json);
char	*new_attr(char *json, t_json_obj *obj);
char	*store_by_type(t_json_obj *obj, char *json);

#endif