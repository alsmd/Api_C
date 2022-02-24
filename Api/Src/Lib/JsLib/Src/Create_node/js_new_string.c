#include <js_lib.h>

/*
	@param		json (a json string that points to the double quoutes of a json value: "flavio")
	@return		Returns a string created with malloc with the value.
*/
char	*js_new_string(char *json)
{
	json++;
	return (strndup(json, strlen_var(json, '"')));
}