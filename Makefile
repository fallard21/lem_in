# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/25 11:33:25 by user              #+#    #+#              #
#    Updated: 2020/10/15 21:26:13 by user             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----- Name -----
NAME 		= lem-in
HEADER_NAME	= lem_in.h struct.h
LIBFT_NAME	= libft.a

# ----- Dir -----
LIBFT_DIR	= ./libft/
LIBFT_INC	= ./libft/includes
SRC_DIR 	= ./sources/
OBJ_DIR		= ./obj/
INC_DIR 	= ./includes/

# ----- Lists -----
FUNCS		= 	bfs.c lem_in.c read_input.c parse.c \
				utils.c utils_2.c free_utils.c free_utils_2.c \
				handle_rooms.c handle_links.c move_ants.c \
				move_ants_utils.c bellman_ford.c direct_graph.c \
				duplicate_rooms.c redirect_links.c save_path.c \
				calculate_step.c sorting.c suurballe.c bonus.c


# ----- Auto -----
HEADER		= $(addprefix $(INC_DIR), $(HEADER_NAME))
LIBFT		= $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
SRC			= $(addprefix $(SRC_DIR), $(FUNCS))
OBJ			= $(addprefix $(OBJ_DIR), $(FUNCS:.c=.o))

# -------------
INCLUDES	= -I $(INC_DIR) -I $(LIBFT_INC) 

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
LFT			= -L $(LIBFT_DIR) -lft

# --- Colors ---
RED				= "\033[0;31m"
GREEN			= "\033[0;32m"
CYAN			= "\033[0;36m"
YELLOW			= "\033[0;33m"
EOC				= "\033[0m"
# =================

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LFT) -o $(NAME)
	@echo $(GREEN) "Program $(NAME) created" $(EOC)

$(OBJ_DIR):
	@mkdir -p ./obj/

FORCE:		;

$(LIBFT): FORCE
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	@echo $(CYAN) "Compiling $< into $@"$(EOC)

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@echo $(YELLOW)"$(NAME):"$(EOC) $(RED)"Object files deleted."$(EOC)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo $(YELLOW)"$(NAME):"$(EOC) $(RED)"Executable file deleted."$(EOC)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
