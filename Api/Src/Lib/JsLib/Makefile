
SRC_DIR = ./Src/

CREATE_DIR = $(SRC_DIR)Create_node/

SEARCH_DIR = $(SRC_DIR)Search_node/

UTIL_DIR = $(SRC_DIR)Util/

CREATE = $(CREATE_DIR)js_new_attr.c $(CREATE_DIR)js_new_obj.c $(CREATE_DIR)js_new_string.c $(CREATE_DIR)js_new_array.c

SEARCH = $(SEARCH_DIR)js_get_value.c $(SEARCH_DIR)js_foreach.c

UTIL = $(UTIL_DIR)whitespace.c $(UTIL_DIR)strlen_var.c $(UTIL_DIR)is_num.c

SRC = $(CREATE) $(SEARCH) $(UTIL)

OBJ = $(SRC:.c=.o)

NAME = libjs.a

HEADER = -I./Include

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADER) -c -o $@ $< 

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: clean fclean re all