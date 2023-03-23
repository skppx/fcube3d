NAME		=	CUB3D
MLX_DIR		=	./minilibx-linux/
SRC_DIR		=	./srcs/
INC_DIR		=	./includes/
SRCS		=	main.c\
				parsing.c\
				parsing_2.c\
				utils.c\
				raycasting.c\
				hexa.c\
				move.c\
				move2.c\
				pole.c\
				draw.c\
				render_frame_utils.c\

SRC_BASENAME    =	$(addprefix $(SRC_DIR), $(SRCS))
OBJS            =	$(SRC_BASENAME:.c=.o)
CC				=	gcc
FLAGS			=	-Wall -Wextra -Werror -fsanitize=address -g3 -I $(MLX_DIR) -I $(INC_DIR) -I ./libft/

.c.o	:
			$(CC) $(FLAGS) -Imlx -c $< -o $@

all	:		$(NAME)

$(NAME)	:	$(OBJS)
			make -C $(MLX_DIR)
			make -C ./libft/
			$(CC) $(FLAGS) -o $(NAME) $(OBJS) -L $(MLX_DIR) -L./libft/ -lft -lmlx -lbsd -lXext -lX11 -lm

clean	:
			rm -rf $(OBJS)
			make fclean -C ./libft/
			make clean -C $(MLX_DIR)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all
