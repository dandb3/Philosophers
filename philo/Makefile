NAME		=	philo
SRCS		=	philo_begin.c philo_error.c philo_free.c philo_init.c philo_msg.c philo_routine.c philo_utils.c philo.c main.c
OBJS		=	$(SRCS:.c=.o)
HEADERS		=	philo_error.h philo_msg.h philo.h
CC			=	cc
RM			=	rm
RMFLAGS		=	-rf

ifeq (test, $(findstring test, $(MAKECMDGOALS)))
	CFLAGS	=
else
	CFLAGS	=	-Werror -Wextra -Wall
endif

all			:	$(NAME)
test		:	$(NAME)

$(NAME)		:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

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
