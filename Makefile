NAME = pipex

SRCS = 	ft_args.c \
		ft_commands.c \
		ft_error.c \
		ft_printf.c \
		ft_put.c \
		ft_split.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_uargs.c \
		main.c \
		pipex.c

INCLUDES =	ft_printf.h \
			pipex.h 

OBJS =	$(SRCS:%.c=%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean :
		rm *.o
	
fclean : clean 
		rm ./pipex

re : fclean all

%.o : %.c $(INCLUDES)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY = all clean fclean re 