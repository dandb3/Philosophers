NAME		=	philo
SRCS		=	philo_begin.c philo_error.c philo_free.c philo_init.c philo_msg.c philo_routine.c philo_utils.c philo.c main.c
OBJS		=	$(SRCS:.c=.o)
HEADERS		=	philo_error.h philo_msg.h philo.h
PTHREAD		=	-pthread
CC			=	cc
CFLAGS		=	-Werror -Wextra -Wall
RM			=	rm
RMFLAGS		=	-rf

all			:	$(NAME)

$(NAME)		:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(PTHREAD) -o $@

%.o			:	%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean		:
	$(RM) $(RMFLAGS) $(OBJS)

fclean		:	clean
	$(RM) $(RMFLAGS) $(NAME)

re			:
	make fclean
	make all

.PHONY		:	all clean fclean re
