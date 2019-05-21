# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dskrypny <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/07 14:30:48 by dskrypny          #+#    #+#              #
#    Updated: 2019/04/30 16:50:11 by dskrypny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

OBJ_DIR = ./objects/
SRC_DIR = ./source/
INC_DIR = ./includes/

SOURCE = changing.c \
		 circle_fractal.c \
		 error.c \
		 fill_img.c \
		 fern_fractal.c \
		 triangle_fractal.c \
		 square_fractal.c \
		 fractal_functions.c \
		 helper.c \
		 iterations.c \
		 hook_key.c \
		 main.c \
		 print_info.c \
		 timer.c

OBJ = $(addprefix $(OBJ_DIR), $(SOURCE:.c=.o))

HEADER = $(addprefix $(INC_DIR), header.h)

FLAGS = -O3 -Wall -Wextra -Werror -I$(INC_DIR)

LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@make -C libft/
	gcc $(FLAGS) -lmlX $(OBJ) -framework OpenGL -framework Appkit $(LIB) -o $(NAME)
	@echo "$(NAME) compiled"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
	@gcc $(FLAGS) -c -o $@ $<

clean:
	@make clean -C libft/
	@rm -rf $(OBJ)
	@echo "obj files deleted"

fclean: clean
	@make fclean -C libft/
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@echo "$(NAME) file deleted"

re: fclean all

vpath %.c $(SRC_DIR)
.PHONY: all clean fclean re

mlx:
	man /usr/share/man/man3/mlx.1

loop:
	man /usr/share/man/man3/mlx_loop.1

image:
	man /usr/share/man/man3/mlx_new_image.1

window:
	man /usr/share/man/man3/mlx_new_window.1

pixel:
	man /usr/share/man/man3/mlx_pixel_put.1

