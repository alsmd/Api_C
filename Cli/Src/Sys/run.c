#include <cli.h>

void	run()
{
	while (1)
	{
		render();
		update();
		usleep(150);
	}
}
