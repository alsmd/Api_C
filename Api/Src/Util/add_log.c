#include <utils.h>

void    add_log(char *method, char *route, int status)
{
    time_t  curtime;
    char    *str_time;
    FILE *file_log = fopen("../Logs/log", "a");

    time(&curtime);
    if (file_log != NULL)
    {
        fprintf(file_log, "{");
        fprintf(file_log, "\"method\": \"%s\", ", method);
        fprintf(file_log, "\"uri\": \"%s\", ", route);
        str_time = strdup(ctime(&curtime));
        str_time[strlen(str_time) - 1] = '\0';
        fprintf(file_log, "\"time\": \"%s\", ", str_time);
        fprintf(file_log, "\"status\": %d", status);
        fprintf(file_log, "}\n");
        fclose(file_log);
    }
    
}