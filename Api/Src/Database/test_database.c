#include <database.h>

void	check(int statement)
{
	if (statement)
		printf("Ok\n");
	else
		printf("Ko\n");
}

void	simple_read()
{
	char	*json;

	json = read_row("pokemon", "name,type", "name='Charmander'");
	check(!strcmp(json, "{{\"name\":\"Charmander\",\"type\":\"Fire\"}}"));

	json = read_row("pokemon", "name,type", "name='Ditto'");
	check(!strcmp(json, "{{\"name\":\"Ditto\",\"type\":\"Normal\"}}"));
	
	json = read_row("pokemon", "name,type", "name='Caterpie'");
	check(!strcmp(json, "{{\"name\":\"Caterpie\",\"type\":\"Bug\"}}"));

	json = read_row("pokemon", "name", "name='Diglett'");
	check(!strcmp(json, "{{\"name\":\"Diglett\"}}"));

	json = read_row("pokemon", "type,name", "name='Caterpie'");
	check(!strcmp(json, "{{\"type\":\"Bug\",\"name\":\"Caterpie\"}}"));

	json = read_row("pokemon", "name,type", "name='Charmander' AND id='1'");
	check(!strcmp(json, "{{\"name\":\"Charmander\",\"type\":\"Fire\"}}"));
}

void	simple_create()
{
	char	*json;

	create_row("pokemon", "name,type", "'my_name','fire'");
	json = read_row("pokemon", "name,type", "name='my_name'");
	check(!strcmp(json, "{{\"name\":\"my_name\",\"type\":\"fire\"}}"));

	create_row("pokemon", "name,type", "'Watermoon','Ground'");
	json = read_row("pokemon", "name,type", "name='Watermoon'");
	check(!strcmp(json, "{{\"name\":\"Watermoon\",\"type\":\"Ground\"}}"));

	create_row("pokemon", "name", "'NullMon'");
	json = read_row("pokemon", "name,type", "name='NullMon'");
	check(!strcmp(json, "{{\"name\":\"NullMon\",\"type\":\"NULL\"}}"));
}

void	simple_update()
{
	char	*json;

	update_row("pokemon", "name='UpdatePokemon',type='TypeUpdated'", "id=1");
	json = read_row("pokemon", "name,type", "id='1'");
	check(!strcmp(json, "{{\"name\":\"UpdatePokemon\",\"type\":\"TypeUpdated\"}}"));

	update_row("pokemon", "name='Pincher',type='Anger'", "id=2");
	json = read_row("pokemon", "name,type", "id='2'");
	check(!strcmp(json, "{{\"name\":\"Pincher\",\"type\":\"Anger\"}}"));
}

void	simple_delete()
{
	char	*json;

	delete_row("pokemon", "id=1");
	json = read_row("pokemon", "name,type", "id='1'");
	check(!strcmp(json, "{}"));

	delete_row("pokemon", "id=2");
	json = read_row("pokemon", "name,type", "id='2'");
	check(!strcmp(json, "{}"));
}

//	Execute:
//	gcc -I../../Includes -I/usr/local/mysql/include ./*.c ./*/*.c  ../Utils/*.c -L/usr/local/mysql/lib -lmysqlclient
//	./a.out
//	rm ./a.out

//	Check if Crud operation is been made successfully
int	main(void)
{
	create_database();
	printf("Simple create tests: \n\n");
	simple_create();
	printf("_________\n");
	printf("Simple read tests: \n\n");
	simple_read();
	printf("_________\n");
	printf("Simple update tests: \n\n");
	simple_update();
	printf("_________\n");
	printf("Simple delete tests: \n\n");
	simple_delete();
	printf("_________\n");
	return (0);
}
