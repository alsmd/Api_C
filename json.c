#include <stdio.h>
#include <string.h>
#include "json.h"
#include <stdlib.h>

t_json_obj	*global;

/***************
 * 
 * 	UTILS
 * 
****************/

int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	strlen_var(char *buffer, char end)
{
	int	index;

	index = 0;
	while (buffer[index] && buffer[index] != end)
		index++;
	return (index);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

char	*jump_whitespace(char *json)
{
	while (is_whitespace(*json))
		json++;
	return (json);
}

/***************
 * 
 * 	UTILS END
 * 
****************/


/***************
 * 
 * 	CREATE NODES
 * 
****************/

char	*store_by_type(t_json_obj *obj, char *json)
{
	if (*json == '"')
	{
		obj->type = JSON_STRING;
		obj->string_value = new_json_string(json);
		json++;
		while (*json != '"')
			json++;
		json++;
	}
/* 	if (**json == '[')
		store_array(obj, json); */
	else if (*json == '{')
	{
		obj->obj_value = calloc(1, sizeof(t_json_obj));
		json = new_json_obj(json, obj->obj_value);

	}
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
	else if (is_number(*json))
	{
		obj->type = JSON_INTEGER;
		obj->int_value = atoi(json);
		while (is_number(*json))
			json++;
	}
	return (json);
}

char	*new_attr(char *json, t_json_obj *obj)
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

char	*new_json_string(char *json)
{
	json++;
	return (strndup(json, strlen_var(json, '"')));
}

char	*new_json_obj(char *json, t_json_obj *o)
{
	t_json_obj	*obj;
	t_json_obj	*begin;

	if (o)
		obj = o;
	else
		obj = calloc(1, sizeof(t_json_obj));
	obj->type = JSON_OBJ;
	begin = obj;
	json += 1;
	while (*json != '}')
	{
		json = jump_whitespace(json);
		if (*json == '}')
			break ;
		if (*json == ',')
		{
			json++;
			json = jump_whitespace(json);
			begin->next = calloc(1, sizeof(t_json_obj));
			begin = begin->next;
			json = new_attr(json, begin);
		}
		else
			json = new_attr(json, begin);
	}
	json++;
	return (json);
}

t_json_obj	*js_convert_json_to_object(char *j)
{
	char		*json;
	t_json_obj	*obj;

	json = strdup(j);
	obj = calloc(1, sizeof(t_json_obj));
	new_json_obj(json, obj);
	free(json);
	return (obj);
}
/***************
 * 
 * 	CREATE NODES END
 * 
****************/

/***************
 * 
 * 	SEARCH NODES
 * 
****************/

t_json_obj	*js_get_value(t_json_obj *obj, char *key)
{
	t_json_obj	*begin;

	begin = obj;
	while (begin)
	{
		if (!strcmp(begin->key, key))
			return (begin);
		begin = begin->next;
	}
	return (0);
}

/***************
 * 
 * 	SEARCH NODES END
 * 
****************/

int	main(void)
{
	t_json_obj	*obj;
	
	
	obj = js_convert_json_to_object("{\"firmness\":{\"name\":\"soft\",\"url\":\"https://pokeapi.co/api/v2/berry-firmness/2/\"},\"growth_time\":3,\"id\":1,\"item\":{\"name\":\"cheri-berry\",\"url\":\"https://pokeapi.co/api/v2/item/126/\"},\"max_harvest\":5,\"name\":\"cheri\",\"natural_gift_power\":60,\"natural_gift_type\":{\"name\":\"fire\",\"url\":\"https://pokeapi.co/api/v2/type/10/\"},\"size\":20,\"smoothness\":25,\"soil_dryness\":15}");

	printf("%s\n", js_get_value(js_get_value(obj, "firmness")->obj_value, "name")->string_value);
	// printf("%s\n", get_obj(obj, "name")->string_value);
	return (0);
}
