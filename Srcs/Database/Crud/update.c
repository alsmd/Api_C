#include <database.h>

int	update_row(char *table, char *new_attrs, char *statement)
{
	MYSQL	*con;
	char	query[4080];
	int		status;

	con = 0;
	init_con(&con);
	sprintf(query, "UPDATE %s SET %s WHERE %s", table, new_attrs, statement);
	status = mysql_query(con, query);
	if (status)
	{
		printf("Error:: %s \n", mysql_error(con));
		return (1);
	}
	mysql_close(con);
	return (0);
}

//UPDATE pokemon SET name = new_name, type = new_type WHERE id = 5