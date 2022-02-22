#ifndef DATABASE_H
#define DATABASE_H
#include <stdarg.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <utils.h>

//Config
#define HOST "localhost"
#define USER "flda-sil"
#define PASS "123"
#define DBNAME "teste"
#define PORT 3306
#define UNIX_SOCKET (void *)0
#define FLAG 0

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
	@param	fields (fields has to be separeted by "," and withou any blank spaces)
	@return	Returns a string in json format
*/
char	*read_row(char *table, char *fields,  char *statement);

/*
	@brief	Update table with new_attrs where statement
	parma	example (update("users", "name = griel, email = teste2@gmail.com", "id = 3"))
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
	@brief	Sed databases with data
*/
int		sed_database(MYSQL *con);

#endif