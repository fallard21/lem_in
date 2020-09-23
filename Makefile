NAME = lem_in

CC = gcc -g
CFLAG = 

HEADER_1 = struct.h
HEADER_2 = lem_parser.h
LIB_NAME = libft.a

SRC_DIR = sources/
INC_DIR = includes/
LIB_DIR = libft/

SRC = print.c \
bfs_list.c \
del_list.c \
bfs_queue.c \
free_mem.c \
lem_in.c \
read_input.c \
parse.c utils.c \
free_utils.c \
handle_rooms.c \
handle_links.c \
create_path.c \
tmp_tools.c \
move_ants.c \
move_ants_utils.c \
normalize_graph.c

TMP = $(addprefix $(SRC_DIR), $(SRC:.c=.o))
HEADER = $(addprefix $(INC_DIR), $(HEADER_1))
LIBFT = $(addprefix $(LIB_DIR), $(LIB_NAME))

INCLUDES = -I $(INC_DIR) -I $(LIB_DIR)$(INC_DIR)

all: $(NAME)

$(NAME): $(TMP)
	$(CC) -o $(NAME) $(TMP) $(INCLUDES) -L $(LIB_DIR) -lft

%.o:%.c
	$(CC) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TMP)

fclean: clean
	rm -f $(NAME)

re: fclean all
