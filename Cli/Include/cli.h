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

typedef struct s_sys
{
	int		method;
	int		uri;
	int		time;
	int		nodes;
	int		qnt_page;
	int		cur_page;
	int		item_per_table;
	int		desloc;
	int		cursor;
	char	*screen;
	t_log	*active_log;
	t_log	*selected_uri;
	char	*default_color;
}	t_sys;

void	add_node(char *buffer);
void	set_size();
void	create_nodes();
void	update_event(int cmd);
int		getch(void);

//Sys
t_log	*get_page(t_log *log);
t_log	*get_active_log(t_log *log);
void	reset_sys();
void	run();

//Components
void	item(t_log *item, int id, int total_request, int method, int uri, int status, int time);
void	header(int id, int total_request, int method, int uri, int status, int time);
//Front
void	fill(int r, int size);
void	render();
void	render_item(void);
void	render_table(t_log *log, int id, int total_request, int method, int uri, int status, int time);
void    clean_term(void);
void	render_helper();
void    clean_term(void);
//Event
void	update();
void	table_item_events(int cmd);
void	table_uri_events(int cmd, t_log *log);
void	table_events(int cmd, t_log *log);

#endif