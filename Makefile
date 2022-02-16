DIRSRC		= ./srcs/

LIBFT		= ./libft/

NAMELFT		= ./libft/libft.a

SRC			= exec.c main.c pipes.c utils.c builtins.c

SRCS		= $(addprefix ${DIRSRC}, ${SRC})

OBJS		= ${SRCS:.c=.o}

NAME		= exec

CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g3

.c.o:
			${CC} ${CFLAGS} -c -I${LIBFT} $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@make all -s -C ./libft
			${CC} ${CFLAGS} ${OBJS} ${NAMELFT} -o ${NAME}

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)
			@make fclean -s -C ./libft

re:			fclean all

.PHONY:		all clean fclean re