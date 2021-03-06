#ifndef API_H
#define API_H
#include <mongoose.h>
#include <database.h>
#include <js_lib.h>

enum e_http_errors
{
	HTTP_NOT_FOUND = 404,
	HTTP_OK = 200,
	NOT_HTTP_MESSAGE = -10,
	HTTP_BAD_REQUEST = 400,
	HTTP_INTERNAL_ERROR = 500,
	HTTP_CREATED = 201
};

//Router
void	router(struct mg_connection *c, struct mg_http_message *request);

//Pokemon Controller

//	@brief	Returns all pokemons
void	show_pokemons(struct mg_connection *c, struct mg_http_message *request);
//	@brief Returns an specific pokemon
void	show_pokemon(struct mg_connection *c, struct mg_http_message *request);
//	@brief Store a new pokemon
void	store_pokemon(struct mg_connection *c, struct mg_http_message *request);
//	@brief Update an specific pokemon
void	update_pokemon(struct mg_connection *c, struct mg_http_message *request);
//	@brief Delete an specific pokemon
void	remove_pokemon(struct mg_connection *c, struct mg_http_message *request);

#endif