# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 15:39:19 by psaulnie          #+#    #+#              #
#    Updated: 2022/10/04 10:01:38 by psaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cub3d
NAME_BONUS	:= cub3d_bonus

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
# CFLAGS	+= -fsanitize=address -g3

DIR_SRCS		:=	srcs
DIR_SRCS_BONUS	:=	srcs_bonus
DIR_OBJS		:=	.objs
DIR_OBJS_BONUS	:=	.objs_bonus
DIR_INCS		:=	inc

DIR_LIBFT	:=	libft
DIR_MLX		:=	mlx

LST_SRCS	:=	algo.c \
				algo_utils.c \
				destroy.c \
				draw.c \
				input.c \
				input_movement.c \
				main.c \
				parsing.c \
				start.c \
				textures.c \
				utils.c \
				get_map.c \
				mouse.c \
				get_map_utils.c

LST_SRCS_BONUS	:=	algo.c \
				algo_utils.c \
				destroy.c \
				draw.c \
				input.c \
				input_movement.c \
				main.c \
				parsing.c \
				start.c \
				textures.c \
				utils.c \
				get_map.c \
				mouse.c \
				get_map_utils.c

LST_OBJS		:=	$(LST_SRCS:.c=.o)
LST_OBJS_BONUS	:=	$(LST_SRCS_BONUS:.c=.o)

LST_INCS	:=	cub3d.h

SRCS	:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS))
OBJS	:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS))

SRCS_BONUS	:=	$(addprefix $(DIR_SRCS_BONUS)/,$(LST_SRCS_BONUS))
OBJS_BONUS	:=	$(addprefix $(DIR_OBJS_BONUS)/,$(LST_OBJS_BONUS))
INCS	:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))


AR_LIBFT	:=	$(DIR_LIBFT)/libft.a
AR_MLX		:= libmlx.dylib

all:	lib ${AR_MLX} $(NAME)

$(NAME):	$(AR_MLX) $(AR_LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@

$(DIR_OBJS)/%.o:	$(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
		$(CC) $(CFLAGS) -I  $(DIR_INCS) -c $< -o $@

$(DIR_OBJS):
		mkdir -p $(DIR_OBJS)

$(DIR_OBJS_BONUS)/%.o:	$(DIR_SRCS_BONUS)/%.c $(INCS) Makefile | $(DIR_OBJS_BONUS)
		$(CC) $(CFLAGS) -I  $(DIR_INCS) -c $< -o $@

$(DIR_OBJS_BONUS):
		mkdir -p $(DIR_OBJS_BONUS)
		
lib:	libft/libft.h
		make -C $(DIR_LIBFT)

${AR_MLX}:	mlx/mlx.h
		make -C $(DIR_MLX)
		mv $(DIR_MLX)/libmlx.dylib libmlx.dylib

bonus:	lib ${AR_MLX} $(NAME_BONUS)

$(NAME_BONUS):	$(AR_MLX) $(AR_LIBFT) $(OBJS_BONUS)
		$(CC) $(CFLAGS) $^ -o $@
	
clean:
		rm -rf $(DIR_OBJS)
		rm -rf $(DIR_OBJS_BONUS)
		make -C $(DIR_LIBFT) clean
		make -C $(DIR_MLX) clean

fclean:	clean
		rm -rf $(NAME)
		rm -rf $(NAME_BONUS)
		make -C $(DIR_LIBFT) fclean
		make -C $(DIR_MLX) clean
		rm libmlx.dylib

re: fclean all

.PHONY:	all clean fclean re