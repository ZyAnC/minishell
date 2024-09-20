NAME = minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror \
	-I ./include -I ./libft/libft -I ./libft/printf -I ./libft/get_next_line
LIBFT := ./libft/libft
PRINTF := ./libft/printf
GETNEXTLINE := ./libft/get_next_line
LIBS := $(LIBFT)/libft.a $(PRINTF)/libftprintf.a $(GETNEXTLINE)/get_next_line.a 

SRCS := ./src/main.c
OBJS := ${SRCS:.c=.o}



all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@${MAKE} -C ${LIBFT}
	@${MAKE} -C ${PRINTF}
	@${MAKE} -C ${GETNEXTLINE}
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)



clean:
	@rm -rf $(OBJS)
	@${MAKE} -C ${LIBFT} clean
	@${MAKE} -C ${PRINTF} clean
	@${MAKE} -C ${GETNEXTLINE} clean


fclean: clean
	@rm -rf $(NAME)
	@${MAKE} -C ${LIBFT} fclean
	@${MAKE} -C ${PRINTF} fclean
	@${MAKE} -C ${GETNEXTLINE} clean


re: fclean all

.PHONY: all clean fclean re
