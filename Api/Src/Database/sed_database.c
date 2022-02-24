#include <database.h>

int	sed_database(MYSQL *con)
{
	if (mysql_query(con, "INSERT INTO pokemon(name, type, gen) VALUES('Charmander', 'Fire', 1)"))
		printf("Error::sed_database.c\n");
	if (mysql_query(con, "INSERT INTO pokemon(name, type, gen) VALUES('Ditto', 'Normal', 1)"))
		printf("Error::sed_database.c\n");
	if (mysql_query(con, "INSERT INTO pokemon(name, type, gen) VALUES('Diglett', 'Ground', 1)"))
		printf("Error::sed_database.c\n");
	if (mysql_query(con, "INSERT INTO pokemon(name, type, gen) VALUES('Caterpie', 'Bug', 1)"))
		printf("Error::sed_database.c\n");
}
