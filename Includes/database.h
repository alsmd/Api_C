#ifndef DATABASE_H
#define DATABASE_H
#include <stdarg.h>
#include <mysql/mysql.h>
#include <stdio.h>

int	init_con(MYSQL **con);

#endif