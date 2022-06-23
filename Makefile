# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 15:39:19 by psaulnie          #+#    #+#              #
#    Updated: 2022/06/23 15:02:33 by psaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	cub3d

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
CFLAGS	+= -fsanitize=address -g3

DIR_SRCS	:=	srcs
DIR_OBJS	:=	.objs
DIR_INCS	:=	inc

DIR_LIBFT	:=	libft
DIR_MLX		:=	mlx

LST_SRCS	:=	draw.c \
				input.c \
				main.c \
				parsing.c \
				start.c \
				textures.c \
				utils.c \
				get_map.c \

LST_OBJS	:=	$(LST_SRCS:.c=.o)

LST_INCS	:=	cub3d.h

SRCS	:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS))
OBJS	:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS))
INCS	:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))


AR_LIBFT	:=	$(DIR_LIBFT)/libft.a
AR_MLX		:= libmlx.dylib

all:	lib $(NAME)

$(NAME):	$(AR_MLX) $(AR_LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@

$(DIR_OBJS)/%.o:	$(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
		$(CC) $(CFLAGS) -I  $(DIR_INCS) -c $< -o $@

$(DIR_OBJS):
		mkdir -p $(DIR_OBJS)

lib:
		make -C $(DIR_LIBFT)
		make -C $(DIR_MLX)
		cp $(DIR_MLX)/libmlx.dylib ./

clean:
		rm -rf $(DIR_OBJS)
		make -C $(DIR_LIBFT) clean
		make -C $(DIR_MLX) clean

fclean:	clean
		rm -rf $(NAME)
		make -C $(DIR_LIBFT) fclean
		make -C $(DIR_MLX) clean
		rm libmlx.dylib

re: fclean all

.PHONY:	all clean fclean re