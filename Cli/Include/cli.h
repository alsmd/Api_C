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

typedef struct s_log
{
	char			*method;
	char			*uri;
	char			*time;
	int				status;
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
	char	*default_color;
}	t_sys;

void	add_node(char *buffer);
void	set_size();
void	create_nodes();
void	print_table(void);
void	fill(int r, int size);
void	check_event(int cmd);
int		getch(void);
t_log	*get_page();

//Components
void	item(t_log *item);
void	header();

#endif