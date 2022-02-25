#ifndef CLI_H
#define CLI_H
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <js_lib.h>
#include <colors.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#define ON 1
#define OFF 0

//@brief	Each Log's json obj will be converted to this structure
typedef struct s_log
{
	int				id;
	char			*method;
	char			*uri;
	char			*time;
	int				status;
	int				total_request;
	js_node			*obj;
	struct s_log	*same_request;
	struct s_log	*next;
}	t_log;

//@brief	Informations needed to implement interative table
typedef struct s_sys
{
	size_t	method;
	size_t	uri;
	size_t	time;
	int		nodes;
	int		item_per_table;
	int		desloc;
	int		cursor;
	char	*screen;
	t_log	*active_log;
	t_log	*selected_uri;
	char	*default_color;
}	t_sys;

// Manipulate nodes
void	add_node(char *buffer);
void	set_size();
void	create_nodes();

/***************
 * 
 * 	SYSTEM
 * 
****************/

/*
	@brief	Get active page from the global logs based on the global sys.desloc
*/
t_log	*get_page(t_log *log);

/*
	@brief	Get active log from the global logs based on the global sys.cursor
*/
t_log	*get_active_log(t_log *log);

/*
	@brief	Reset sys component as sys.cursor and sys.desloc
*/
void	reset_sys();

/*
	@brief	Start the cli in a infinite loop.
*/
void	run();

/*
	@brief	free the system resources
*/
void	free_system();

/***************
 * 
 * 	Components
 * 
****************/

/*
	@brief	Print an item log as a table item, you can turn ON or OFF a specific column
*/
void	item(t_log *item, int id, int total_request, int method, int uri, int status, int time);

/*
	@brief	Print the table's header bases on the flags that are ON or OFF
*/
void	header(char *title, int id, int total_request, int method, int uri, int status, int time);


/***************
 * 
 * 	Frontend
 * 
****************/

/*
	@brief	It will print all the visuals of our application
*/
void	render();

/*
	@brief	It will print the item that is stored at sys.active_log
*/
void	render_item(void);

/*
	@brief	Render the table based on log's chain passed as parameter
*/
void	render_table(t_log *log, char *title, int id, int total_request, int method, int uri, int status, int time);

/*
	@brief	Render the helper menu.
*/
void	render_helper();

void    clean_term(void);
void	fill(int r, int size);

/***************
 * 
 * 	Events
 * 
****************/

/*
	@brief	Listen and execute events
*/
void	update();

/*
	@brief	Events for the page Item
*/
void	table_item_events(int cmd);

/*
	@brief	Event for the page Uri
*/
void	table_uri_events(int cmd, t_log *log);

/*
	@brief	Event from the main page
*/
void	table_events(int cmd, t_log *log);

//Utils
int		getch(void);
#endif