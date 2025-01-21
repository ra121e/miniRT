# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 18:35:52 by xlok              #+#    #+#              #
#    Updated: 2025/01/21 20:29:35 by xlok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

BONUS_NAME := miniRT_bonus

LIB_DIR := libft
LIB := $(LIB_DIR)/libft.a
MLX_DIR := mlx
MLX_LIB := $(MLX_DIR)/libmlx.a

CC := cc
CFLAGS := -g -Wall -Werror -Wextra
INC := inc/miniRT.h
BONUS_INC := inc/miniRT_bonus.h
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
		 assign.c \
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

BONUS_SRC_DIR := bonus_src
BONUS_SRC_F := main_bonus.c \
			 utils_bonus.c \
			 input_validation_bonus.c \
			 validate_utils_bonus.c \
			 validate_acl_bonus.c \
			 validate_obj_bonus.c \
			 init_bonus.c \
			 init_utils_bonus.c \
			 init_file_bonus.c \
			 init_acl_bonus.c \
			 init_obj_bonus.c \
			 handler_bonus.c \
			 ft_atof_bonus.c \
			 vec3_bonus.c \
			 vec3_fnc_bonus.c \
			 dlist_bonus.c \
			 assign_bonus.c \
			 math_bonus.c \
			 lighting_bonus.c \
			 drawing_bonus.c \
			 raytracing_bonus.c \
			 fcolor_bonus.c \
			 fcolor_fnc_bonus.c \
			 move_camera_bonus.c

BONUS_SRC := $(BONUS_SRC_F:%.c=$(BONUS_SRC_DIR)/%.c)

BONUS_OBJ_DIR := bonus_obj
BONUS_OBJ := $(BONUS_SRC_F:%.c=$(BONUS_OBJ_DIR)/%.o)

.PHONY: all clean fclean re bonus norm

all: $(NAME)

$(NAME): $(LIB) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINK) -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIB) $(MLX_LIB) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LINK) -o $@

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

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c $(BONUS_INC)
	@mkdir -p $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR) $(MLX_DIR)/obj

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME) $(LIB) $(MLX_DIR)

re: fclean all

norm:
	clear
	@norminette $(SRC) $(INC) $(BONUS_SRC) $(BONUS_INC)
