#include <database.h>

static char *host = "localhost";
static char	*user = "flda-sil";
static char *pass = "123";
static char	*dbname = "teste";

unsigned int port = 3306;
static char	*unix_socket = (void *)0;
unsigned int flag = 0;

int	init_con(MYSQL **con)
{
	*con = mysql_init(NULL);
	if (!mysql_real_connect(*con, host, user, pass, dbname, port, unix_socket, flag))
	{
		printf("Error %s [%d]\n", mysql_error(*con), mysql_errno(*con));
		exit(1);
	}
}