NAME = server

# Files Separeted by directory

CONTROLLER_DIR = ./Src/Controller/

CONTROLLERS = $(CONTROLLER_DIR)PokemonController.c

MODULE_DIR = ./Src/Module/

MODULE = $(MODULE_DIR)create.c $(MODULE_DIR)read.c $(MODULE_DIR)update.c $(MODULE_DIR)delete.c

DATABASE_DIR = ./Src/Database/

DATABASE = $(DATABASE_DIR)con.c $(DATABASE_DIR)create_database.c $(DATABASE_DIR)sed_database.c

LIB_DIR = ./Src/Lib/

LIB = $(LIB_DIR)mongoose.c

ROUTER_DIR = ./Src/Router/

ROUTER = $(ROUTER_DIR)router.c

UTILS_DIR = ./Src/Util/

UTILS = $(UTILS_DIR)split.c $(UTILS_DIR)strjoin.c $(UTILS_DIR)free_matriz.c

#All Files
SRC = ./Src/main.c ./Src/json.c $(CONTROLLERS) $(MODULE) $(DATABASE) $(LIB) $(ROUTER) $(UTILS)

DB_SRC = $(DATABASE_DIR)/main.c $(DATABASE) $(UTILS)

OBJS = $(SRC:.c=.o)

DB_OBJS = $(DB_SRC:.c=.o)

CC = gcc

CFLAGS = 

HEADER = ./Include -I/usr/local/mysql/include

MYSQL_LIB = -L/usr/local/mysql/lib -lmysqlclient

all: $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -I$(HEADER) -c -o $@ $< $(MYSQL_LIB)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(HEADER) -o $(NAME) $(OBJS) $(MYSQL_LIB)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

db: fclean $(DB_OBJS)
	$(CC) $(CFLAGS) -I$(HEADER) -o create_db $(DB_OBJS) $(MYSQL_LIB)
	./create_db
	rm -rf ./create_db

re: fclean all

run: all
	./$(NAME)

.PHONY: clean fclean re all