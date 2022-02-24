#include <database.h>

//	@brief	Get the properties of the row 
static char	*get_properties(MYSQL_ROW row, int num_fields, char *fields, int *types)
{
	int		first;
	char	*buffer;
	char	**keys;
	char	**tmp;

	keys = split(fields, ',');
	tmp = keys;
	buffer = strdup("");
	first = 1;
	for(int i = 0; i < num_fields; i++)
	{
		if (!first)
			buffer = strjoin(buffer, ", ");
		char	key[1024];
		sprintf(key, "\"%s\": ", *keys);
		buffer = strjoin(buffer, key);
		if (row[i])
		{
			char	value[1024];
			if (types[i] == MYSQL_TYPE_STRING || types[i] == MYSQL_TYPE_VARCHAR \
				|| types[i] == MYSQL_TYPE_VAR_STRING)
				sprintf(value, "\"%s\"", row[i]);
			else
				sprintf(value, "%s", row[i]);
			buffer = strjoin(buffer, value);
		}
		else
			buffer = strjoin(buffer, "\"NULL\"");
		keys += 1;
		first = 0;
	}
	free(tmp);
	return (buffer);
}

int		*get_types(MYSQL_RES *result, int num_fields)
{
	int		index;
	int		*types;

	types = calloc (num_fields, sizeof(int));
	MYSQL_FIELD *field;
	index = 0;
	while((field = mysql_fetch_field(result)))
	{
		types[index] = field->type;
		index++;
	}
	return (types);
}

//	@brief	Get the results of the last SELECT query and convert to json
static char	*get_json_result(MYSQL *con, char *fields)
{
	int		first[2];
	char	*buffer;
	int		*types;
	first[0] = 1;
	buffer = strdup("{");
	MYSQL_RES *result = mysql_store_result(con);
	int num_fields = mysql_num_fields(result);
	types = get_types(result, num_fields);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)))
	{
		if (!first[0])
			buffer = strjoin(buffer, ", ");
		buffer = strjoin(buffer, "{");
		buffer = strjoin(buffer, get_properties(row, num_fields, fields, types));
		first[0] = 0;
		buffer = strjoin(buffer, "}");
	}
	buffer = strjoin(buffer, "}");
	mysql_free_result(result);
	return (buffer);
}

char	*read_row(char *table, char *fields,  char *statement)
{
	char	*result;
	MYSQL	*con;
	char	query[4080];
	int		status;

	con = 0;
	init_con(&con);
	if (statement)
		sprintf(query, "SELECT %s FROM %s WHERE %s", fields, table, statement);
	else
		sprintf(query, "SELECT %s FROM %s", fields, table);
	status = mysql_query(con, query);
	result = get_json_result(con, fields);
	if (status)
	{
		printf("Error:: %s \n", mysql_error(con));
		free(result);
		return (NULL);
	}
	mysql_close(con);
	return (result);
}
