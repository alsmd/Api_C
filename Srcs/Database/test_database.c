#include <database.h>

void	check(int statement)
{
	if (statement)
		printf("Ok\n");
	else
		printf("Ko\n");
}
void	simple_search()
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

int	main(void)
{
	create_database();
	printf("Simple search tests: \n\n");
	simple_search();
	printf("_________\n");
	printf("Simple create tests: \n\n");
	simple_create();
	printf("_________\n");
}
