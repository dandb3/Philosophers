NAME		=	philo_bonus
SRCS		=	main_bonus.c philo_bonus.c philo_error_bonus.c \
				philo_free1_bonus.c philo_free2_bonus.c \
				philo_init_bonus.c philo_manage_bonus.c \
				philo_msg_bonus.c philo_routine_bonus.c \
				philo_utils_bonus.c philo_wait_bonus.c
OBJS		=	$(SRCS:.c=.o)
HEADER		=	philo_bonus.h philo_error_bonus.h philo_msg_bonus.h
LINK		=	-pthread

CC			=	cc
CFLAGS		=	-Werror -Wextra -Wall

RM			=	rm
RFLAGS		=	-rf

all		:	$(NAME)
bonus	:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $^ $(LINK) -o $@

%.o		:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $<

clean	:
	$(RM) $(RFLAGS) $(OBJS)

fclean	:	clean
	$(RM) $(RFLAGS) $(NAME)

re		:
	make fclean
	make all

.PHONY	:	all bonus re clean fclean
