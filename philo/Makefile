NAME = philo
OBJS_DIR = objs


SRCS = $(notdir $(wildcard *.c))
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CC = gcc
CFLAGS = -Werror -Wextra -Wall

############################################################################

all: $(NAME)

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) -g $(OBJS) -o $@ -pthread

$(OBJS_DIR)/%.o: %.c 
	@if [ ! -d $(OBJS_DIR) ]; then	\
		mkdir $(OBJS_DIR);			\
		echo mkdir $(OBJS_DIR);		\
	fi
	@$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)/*.o
fclean:
	rm -rf $(OBJS_DIR)/*.o
	rm -rf $(NAME)

re: fclean all

############################################################################


.PHONY: all clean fclean re 