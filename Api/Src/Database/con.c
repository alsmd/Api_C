#include <database.h>

int	init_con(MYSQL **con)
{
	*con = mysql_init(NULL);
	if (!mysql_real_connect(*con, HOST, USER, PASS, DBNAME, PORT, UNIX_SOCKET, FLAG))
	{
		printf("Error %s [%d]\n", mysql_error(*con), mysql_errno(*con));
		exit(1);
	}
	return (0);
}
