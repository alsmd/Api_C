#include <database.h>

int	delete_row(char *table, char *statement)
{
	MYSQL	*con;
	char	query[4080];
	int		status;

	con = 0;
	init_con(&con);
	sprintf(query, "DELETE FROM %s WHERE %s", table, statement);
	status = mysql_query(con, query);
	if (status)
		printf("Error:: %s \n", mysql_error(con));
	mysql_close(con);
}
