#ifndef DATABASE_H
#define DATABASE_H
#include <stdarg.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <utils.h>
#include <curl/curl.h>
#include <js_lib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Config
#define HOST "mysql_container"
#define USER "root"
#define PASS ""
#define DBNAME "api"
#define PORT 3306
#define UNIX_SOCKET (void *)0
#define FLAG 0

//TABLES
typedef struct s_pokemon
{
	char	*name;
	char	*type;
	char	*gen;
}	t_pokemon;

//Init Connexion with config
int	init_con(MYSQL **con);

//CRUD 

/*
	@brief	Create new register into table with keys and values
	@param	example (create("users", "name, email, password", "flavio, teste@gmail.com, teste123"))
*/
int		create_row(char *table, char *keys, char *values);

/*
	@brief	Read from table and get Fields Where Statement (if present).
	@param	example (char *result_json = read("users",  "name,email", "id = 5"))
	@param	fields (fields has to be separeted by "," and without any blank spaces)
	@return	Returns a string in json format
*/
char	*read_row(char *table, char *fields,  char *statement);

/*
	@brief	Update table with new_attrs where statement
	parma	example (update("users", "name = griel,email=teste2\@gmail.com", "id = 3"))
*/
int		update_row(char *table, char *new_attrs, char *statement);

/*
	@brief	Delete from table where statement
*/
int		delete_row(char *table, char *statement);

//CREATE DATABASE

/*
	@brief	Create tables and Populate them.
*/
int		create_database(void);

/*
	@brief	Seed databases with data
*/
int		seed_database();


#endif