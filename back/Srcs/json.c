#include <json.h>

//	@brief	Returns the length of the json's key or value
static int	attr_len(char *json_attr)
{
	int	index;

	index = 0;
	while (json_attr[index] != '"' && json_attr[index])
		index++;
	return (index);
}

//	@brief	Given a json string on the format "key": "value" the key is returned
static char	*get_key(char *json)
{
	while (*json == ' ' || *json == '"')
		json++;
	return (strndup(json, attr_len(json)));
}

//	@brief	Given a json string on the format "key": "value" the value is returned
static char	*get_value(char *json)
{
	while (*json != ':')
		json++;
	json++;
	while (*json == ' ' || *json == '"')
		json++;
	return (strndup(json, attr_len(json)));
}

void	convert_json_to_object(const char *json_obj, int qnt_prop, ...)
{
	char		**argv;
	char		*key;
	char		**value;
	int			index;
	va_list		ptr;
	va_list		tmp;

	va_start(ptr, qnt_prop);
	va_copy(tmp, ptr);
	json_obj += 1;
	argv = split(json_obj, ',');
	while (*argv)
	{
		index = 0;
		while (index < qnt_prop)
		{
			key = va_arg(ptr, char *);
			value = va_arg(ptr, char **);
			if (!strcmp(key, get_key(*argv)))
				*value = get_value(*argv);
			index++;
		}
		va_copy(ptr, tmp);
		argv++;
	}
	va_end(ptr);
}
