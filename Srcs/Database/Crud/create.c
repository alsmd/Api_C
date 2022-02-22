#include <database.h>

int	create_row(char *table, char *keys, char *values)
{
	MYSQL	*con;
	char	query[4080];
	int		status;

	con = 0;
	init_con(&con);
	sprintf(query, "INSERT INTO %s (%s) VALUES (%s)", table, keys, values);
	status = mysql_query(con, query);
	if (status)
		printf("Error:: %s \n", mysql_error(con));
	mysql_close(con);
}
