# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daviles- <daviles-@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 16:56:46 by daviles-          #+#    #+#              #
#    Updated: 2024/05/23 17:53:34 by daviles-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
##########################   COMPILING SETTINGS   #########################
CC = gcc
CFLAGS = -Werror -Wextra -Wall -Wunreachable-code -Ofast #-g3 -fsanitize=address 
RM = rm -f

##########################		DIRS		#################################
SRC_DIR = src
OBJ_DIR = obj
HEADERS = -I ./include -I $(MLX_DIR)/include #include/cub3d2.h 

#########################		LIBS		#################################
LIBFT_DIR = external/libft/
LIBFT = $(LIBFT_DIR)libft.a

# MLX_DIR = external/mlx/
MLX_DIR = ./external/mlx42
# MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -L $(MLX_DIR) #MAC
# MLX_CFLAGS = -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext -lz 
MLX_CFLAGS = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

###########################    FILES   ####################################
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

#########################  COLORS & EXTRAS  #################################
COLOR_RESET = \033[0m
COLOR_RED = \033[0;31m
COLOR_RED_N = \033[1;31m
COLOR_GREEN = \033[0;32m
COLOR_GREEN_N = \033[1;32m
COLOR_YELLOW = \033[0;33m
COLOR_YELLOW_N = \033[1;33m
COLOR_BLUE = \033[0;34m
COLOR_BLUE_N = \033[1;34m
COLOR_PURPLE = \033[0;35m
COLOR_PURPLE_N = \033[1;35m
NOC		=	\033[0m

CHANGES_MADE = 0
CHARS_LEN := 0
CHARS := 0
progress := 4

all: libmlx $(NAME)
	@if [ "$(CHANGES_MADE)" -eq "0" ]; then \
		echo "$(COLOR_RED)No hay cambios para hacer. $(COLOR_RESET)"; \
	fi
	$(call print_progress)
	$(eval progress := 50)
	$(call print_progress)
	$(eval progress := 100)
	$(call print_progress)
	@echo ""

libmlx:
	@echo "$(COLOR_BLUE) Creating MLX! $(COLOR_RESET)"
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4  > /dev/null
	@echo "$(COLOR_BLUE) MLX done $(COLOR_RESET)"

$(NAME):$(OBJ) $(LIBFT) 
	@$(CC) $(OBJ) $(MLX_CFLAGS) $(HEADERS) $(LIBFT) -o $(NAME)
	@$(eval CHANGES_MADE=1)

$(LIBFT):
	@make -C $(LIBFT_DIR) > /dev/null

define print_progress
	@printf "\r$(COLOR_GREEN)[$(COLOR_GREEN_N) %d%%%*.*s $(COLOR_GREEN)] $(COLOR_PURPLE_N)CUB3D $(COLOR_PURPLE)Compiling 🛠️$(COLOR_RESET)" $(progress) $(CHARS_LEN) $(CHARS)
endef

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<  $(HEADERS)
	$(eval progress=$(shell echo $$(($(progress) + 1))))
	$(call print_progress)
# @echo "$(COLOR_BLUE) Created! 😸 $(COLOR_RESET)"

clean:
	@rm -rf $(OBJ_DIR) $(LIBFT) > /dev/null
	@make clean -C $(LIBFT_DIR) > /dev/null
	@rm -rf $(MLX_DIR)/build > /dev/null
	@echo "$(COLOR_RED_N) Cleaned objects and libs! 🧹 $(COLOR_RESET)"


fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) > /dev/null
	@echo "$(COLOR_RED_N) Cleaned all! 🧹 $(COLOR_RESET)"

normi:
	norminette

re: fclean all

.PHONY: all, clean, fclean, re, libmlx


# @echo "$(COLOR_YELLOW)──▄────▄▄▄▄▄▄▄────▄───"
# @echo "─▀▀▄─▄█████████▄─▄▀▀──"
# @echo "─────██─▀███▀─██──────"
# @echo "───▄─▀████▀████▀─▄────"
# @echo "─▀█────██▀█▀██────█▀──$(NOC)"
#After clone repo execute those cmds:
#$ git submodule init
#$ git submodule update
