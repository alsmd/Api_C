#include <database.h>

int		create_tables(MYSQL *con)
{
	/* if (mysql_query(con, "DROP TABLE IF EXISTS pokemon"))
	{
		printf("Error::create_database");
		exit(1);
	} */
	if (mysql_query(con, "CREATE TABLE IF NOT EXISTS pokemon(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), type VARCHAR(255), gen INT)"))
	{
		printf("Error::create_database");
		exit(1);
	}
	return (0);
}

int	create_database(void)
{
	MYSQL	*con;

	init_con(&con);
	create_tables(con);
	mysql_close(con);
	mysql_library_end();
	char	*json = read_row("pokemon", "id", 0);
	if (!strcmp(json, "[]"))
		seed_database();
	return (0);
}
