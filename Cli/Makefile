NAME = cli

# Files Separeted by directory

SRC_DIR = ./Src/

JS_LIB_DIR = $(SRC_DIR)JsLib/

JS_NAME = libjs.a

#All Files
SRC = $(SRC_DIR)main.c $(SRC_DIR)table.c $(SRC_DIR)node.c $(SRC_DIR)getch.c


OBJS = $(SRC:.c=.o)

CC = gcc

CFLAGS = 

HEADER = ./Include -I/usr/local/mysql/include -I$(JS_LIB_DIR)Include

MYSQL_LIB = -L/usr/local/mysql/lib -lmysqlclient

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HEADER) -c -o $@ $< $(MYSQL_LIB)

$(NAME): $(JS_LIB_DIR)$(JS_NAME) $(OBJS)
	$(CC) $(CFLAGS) -I$(HEADER) -o $(NAME) $(OBJS) $(MYSQL_LIB) -L$(JS_LIB_DIR) -ljs

$(JS_LIB_DIR)$(JS_NAME):
	make -C $(JS_LIB_DIR)

clean:
	make clean -C $(JS_LIB_DIR)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(JS_LIB_DIR)
	rm -rf $(NAME)

re: fclean all
	make re -C $(JS_LIB_DIR)
run: all
	./$(NAME)

.PHONY: clean fclean re all