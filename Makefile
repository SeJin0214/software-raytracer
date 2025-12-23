# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/20 15:07:14 by sejjeong          #+#    #+#              #
#    Updated: 2025/12/23 17:23:50 by sejjeong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -O3 -march=native 
#-fno-stack-protector

RM = rm
RFLAGS = -rf

LIBFT_DIR = ./libft
MLX_DIR = ./mlx
OBJS_NAME = objs

INCLUDE_DIR = ./header
INCLUDE = -I $(INCLUDE_DIR)
LIBFT_INCLUDE = -I $(LIBFT_DIR)
MLX_INCLUDE = -I $(MLX_DIR)

LIBFT_LINK = -L $(LIBFT_DIR) -l ft
MLX_LINK = -L $(MLX_DIR) -l mlx_Linux
LIBRARY_LINK = -L/user/lib -l Xext -l X11 -l m -l bsd

LINK = $(LIBFT_LINK) $(MLX_LINK) $(LIBRARY_LINK)

CORE_DIR = ./core

SRCS = $(CORE_DIR)/main.c \
	$(CORE_DIR)/camera.c \
	$(CORE_DIR)/cylinder_object.c \
	$(CORE_DIR)/cylinder_action.c \
	$(CORE_DIR)/cone.c \
	$(CORE_DIR)/cone_action.c \
	$(CORE_DIR)/equation.c \
	$(CORE_DIR)/hit_record.c \
	$(CORE_DIR)/init_canvas.c \
	$(CORE_DIR)/parse.c \
	$(CORE_DIR)/parse_util.c \
	$(CORE_DIR)/parse_solid_shape.c \
	$(CORE_DIR)/plane.c \
	$(CORE_DIR)/plane_action.c \
	$(CORE_DIR)/ray.c \
	$(CORE_DIR)/render.c \
	$(CORE_DIR)/shadow.c \
	$(CORE_DIR)/solid_shape.c \
	$(CORE_DIR)/sphere.c \
	$(CORE_DIR)/sphere_action.c \
	$(CORE_DIR)/world.c \
	$(CORE_DIR)/render_util.c \
	$(CORE_DIR)/light.c \
	$(CORE_DIR)/quaternion.c \
	$(CORE_DIR)/input_object.c \
	$(CORE_DIR)/input_camera.c \
	$(CORE_DIR)/input_light.c \

OBJS = ${SRCS:.c=.o}
ASM = ${SRCS:.c=.s}

OBJECTS = $(OBJS)

all: $(NAME)

$(NAME): $(OBJECTS)
		make -C $(MLX_DIR)
		make -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT_INCLUDE) $(MLX_INCLUDE) $^ $(LINK) -o $@

%.o: %.c
	touch $<
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT_INCLUDE) $(MLX_INCLUDE) -c $< -o $@
%.s: %.c
	touch $<
	$(CC) $(CFLAGS)  $(INCLUDE) $(LIBFT_INCLUDE) $(MLX_INCLUDE) -S $< -o $@

clean:
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean
	$(RM) $(RFLAGS) $(OBJS)
	$(RM) $(RFLAGS) $(BONUS_OBJS)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(RFLAGS) $(NAME)

re: 
	make fclean 
	make all

.PHONY : all clean fclean re
