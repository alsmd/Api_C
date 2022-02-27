#include <api.h>
struct mg_mgr	mongoose;

static void	handle_request(struct mg_connection *c, int event, void *event_data, void *fn_data)
{
	(void)fn_data;
	if (event == MG_EV_HTTP_MSG)
		router(c, (struct mg_http_message *) event_data);
}

char    *get_ip()
{
	char hostbuffer[256];
	char *IPbuffer;
	struct hostent *host_entry;

	// To retrieve hostname
	gethostname(hostbuffer, sizeof(hostbuffer));
	// To retrieve host information
	host_entry = gethostbyname(hostbuffer);
	// To convert an Internet network
	// address into ASCII string
	IPbuffer = inet_ntoa(*((struct in_addr*)
						   host_entry->h_addr_list[0]));
	return (IPbuffer);
}

void	logout(int signal)
{
	(void)signal;
	mg_mgr_free(&mongoose);
	exit(0);
}

int	main(void)
{
	char            address[1024];
	char            *ip;

	ip = get_ip();
	sprintf(address, "%d:8000", ip);
	signal(SIGINT, logout);
	mg_mgr_init(&mongoose);
	mg_http_listen(&mongoose, address, handle_request, &mongoose);
	while (true)
		mg_mgr_poll(&mongoose, 1000);
	mg_mgr_free(&mongoose);
}