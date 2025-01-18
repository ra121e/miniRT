# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 18:35:52 by xlok              #+#    #+#              #
#    Updated: 2025/01/18 12:32:44 by athonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

LIB_DIR := libft
LIB := $(LIB_DIR)/libft.a
MLX_DIR := mlx
MLX_LIB := $(MLX_DIR)/libmlx.a

CC := cc
CFLAGS := -g -Wall -Werror -Wextra
INC := inc/miniRT.h
INC_FLAG := -Iinc -I$(LIB_DIR)/inc -I$(MLX_DIR)
LINK := -L$(LIB_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SRC_DIR := src
SRC_F := main.c \
		 utils.c \
		 input_validation.c \
		 validate_utils.c \
		 validate_acl.c \
		 validate_obj.c \
		 init.c \
		 init_utils.c \
		 init_file.c \
		 init_acl.c \
		 init_obj.c \
		 handler.c \
		 ft_atof.c \
		 vec3.c \
		 vec3_fnc.c \
		 dlist.c \
		 math.c \
		 lighting.c \
		 drawing.c \
		 raytracing.c \
		 fcolor.c \
		 fcolor_fnc.c \
		 move_camera.c

SRC := $(SRC_F:%.c=$(SRC_DIR)/%.c)

OBJ_DIR := obj
OBJ := $(SRC_F:%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean fclean re bonus norm

all: $(NAME)

$(NAME): $(LIB) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINK) -o $@

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		rm -rf minilibx-linux; \
		git clone https://github.com/42Paris/minilibx-linux.git mlx; \
	fi
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR) $(MLX_DIR)/obj

fclean: clean
	rm -rf $(NAME) $(LIB) $(MLX_DIR)

re: fclean all

norm:
	clear
	@norminette $(SRC) $(INC)
