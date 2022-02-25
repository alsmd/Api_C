#include <cli.h>

extern int		helper;

void	update()
{
	int		cmd;

	cmd = getch();
	if (cmd == 'q')
		exit(0);
	update_event(cmd);
}