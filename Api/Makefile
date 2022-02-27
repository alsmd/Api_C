NAME = server

# Files Separeted by directory

CONTROLLER_DIR = ./Src/Controller/

CONTROLLERS =	$(CONTROLLER_DIR)PokemonController/remove_pokemon.c $(CONTROLLER_DIR)PokemonController/show_pokemon.c \
				$(CONTROLLER_DIR)PokemonController/store_pokemon.c $(CONTROLLER_DIR)PokemonController/update_pokemon.c

MODULE_DIR = ./Src/Module/

MODULE = $(MODULE_DIR)create.c $(MODULE_DIR)read.c $(MODULE_DIR)update.c $(MODULE_DIR)delete.c

DATABASE_DIR = ./Src/Database/

DATABASE = $(DATABASE_DIR)con.c $(DATABASE_DIR)create_database.c $(DATABASE_DIR)seed_database.c

LIB_DIR = ./Src/Lib/

LIB = $(LIB_DIR)mongoose.c

JS_LIB_DIR = $(LIB_DIR)JsLib/

JS_NAME = libjs.a

ROUTER_DIR = ./Src/Router/

ROUTER = $(ROUTER_DIR)router.c

UTILS_DIR = ./Src/Util/

UTILS = $(UTILS_DIR)split.c $(UTILS_DIR)strjoin.c $(UTILS_DIR)free_matriz.c $(UTILS_DIR)add_log.c

#All Files
SRC = ./Src/main.c $(CONTROLLERS) $(MODULE) $(DATABASE) $(LIB) $(ROUTER) $(UTILS)

DB_SRC = $(DATABASE_DIR)/main.c $(DATABASE) $(UTILS)

OBJS = $(SRC:.c=.o)

DB_OBJS = $(DB_SRC:.c=.o) $(MODULE:.c=.o)

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

HEADER = ./Include -I/usr/local/mysql/include -I$(JS_LIB_DIR)Include

MYSQL_LIB = -L/usr/local/mysql/lib -lmysqlclient

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HEADER) -c -o $@ $< $(MYSQL_LIB)

$(NAME): $(JS_LIB_DIR)$(JS_NAME) $(OBJS)
	$(CC) $(CFLAGS) -I$(HEADER) -o $(NAME) $(OBJS) $(MYSQL_LIB) -L$(JS_LIB_DIR) -ljs -lcurl

$(JS_LIB_DIR)$(JS_NAME):
	make -C $(JS_LIB_DIR)

clean:
	make clean -C $(JS_LIB_DIR)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(JS_LIB_DIR)
	rm -rf $(NAME)

db: $(JS_LIB_DIR)$(JS_NAME) $(DB_OBJS)
	$(CC) $(CFLAGS) -I$(HEADER) -o create_db $(DB_OBJS)  $(MYSQL_LIB) -L$(JS_LIB_DIR) -ljs -lcurl 
	./create_db
	rm -rf ./create_db $(DATABASE)main.o

re: fclean all
	make re -C $(JS_LIB_DIR)
run: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: clean fclean re all