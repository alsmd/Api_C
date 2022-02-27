#include <database.h>

int	request_content(char *url, char *file)
{
	FILE		*g_content;
	CURL		*curl;
	CURLcode	result;
	int			status;

	g_content = fopen(file, "wb");
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, g_content);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
		result = curl_easy_perform(curl);
		if (result == CURLE_OK)
			status = 0;
		if (result != CURLE_OK)
			status = 1;
		fclose(g_content);
		curl_easy_cleanup(curl);
	}
	return (status);
}

static char	*get_content(char *file)
{
	char	*buffer = strdup("");
	char	*chunk = calloc(1000, sizeof(char));
	int		fd = open(file, O_RDONLY);	

	if (file)
	{
		while (read(fd, chunk, 1000))
		{
			buffer = strjoin(buffer, chunk);
			bzero(chunk, 1000);
		}
		free(chunk);
	}
	close(fd);
	return (buffer);
}

int	seed_database()
{
	char	*url = strdup("https://pokeapi.co/api/v2/pokemon/?limit=1");
	char	*tmp_file = "./.tmp_file";
	js_node	response;
	js_node	*result;
	char	*json;

	for (int i = 1; i < 151; i++)
	{
		request_content(url, tmp_file);
		json = get_content(tmp_file);
		js_new_obj(json, &response);
		free(url);
		url = strdup(js_get_value(response.obj_value, "next")->string_value);
		result = js_get_value(response.obj_value, "results")->array_value;
		char	value[512];
		int		gen;
		gen = i <= 151 ? 1 : 2;
		sprintf(value, "'%s', '%d'", js_get_value(result->obj_value, "name")->string_value, gen);
		if (create_row("pokemon", "name, gen", value))
			printf("Error storing %s into the database\n", value);
		else
			printf("%s stored successfuly!\n", value);
		free(json);
		js_clean_obj(response.obj_value);
	}
	free(url);
	unlink(tmp_file);
	return (0);
}