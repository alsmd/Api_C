#include <cli.h>

void	render_helper()
{
	write(1, YELLOW_LIGHT, 8);
	write(1, "\"w/s\" to scroll throught the table.\n", 37);
	write(1, "[Enter] to select a request\n", 29);
	write(1, "[Backspace] returns to Log Table\n", 34);
	write(1, "\"q\" to quit.\n", 14);
	write(1, RESET, 7);
}