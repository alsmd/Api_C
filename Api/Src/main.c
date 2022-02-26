#include <api.h>

static void	handle_request(struct mg_connection *c, int event, void *event_data, void *fn_data)
{
	if (event == MG_EV_HTTP_MSG)
		router(c, (struct mg_http_message *) event_data);
}

int	main(void)
{
	struct mg_mgr	mongoose;

	char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;
  
    // To retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
  
    // To retrieve host information
    host_entry = gethostbyname(hostbuffer);
  
    // To convert an Internet network
    // address into ASCII string
    IPbuffer = inet_ntoa(*((struct in_addr*)
                           host_entry->h_addr_list[0]));
	sprintf(hostbuffer, "%s:8000", IPbuffer);
	mg_mgr_init(&mongoose);
	mg_http_listen(&mongoose, hostbuffer, handle_request, &mongoose);
	while (true)
		mg_mgr_poll(&mongoose, 1000);
	mg_mgr_free(&mongoose); 
}
//--domainname string