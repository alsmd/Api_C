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

typedef struct s_size
{
	int	method;
	int	uri;
	int	time;
	int	nodes;
	int	qnt_page;
	int	cur_page;
	int	item_per_table;
	int	desloc;
}	t_size;

void	add_node(char *buffer);
void	set_sizes();
void	create_nodes();
void	print_table(void);
void	fill(int r, int size);
void	execute_action(int cmd);
int		getch(void);

#endif