NAME = philo

SRCS = $(notdir $(wildcard *.c))
OBJS = $(SRCS:.c=.o)
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
	@$(CC) $(CFLAGS) -g -c $< -o $@ -L $(LIBS_DIR) -lft -I $(INCS_DIR)

$(LIBFT):
	make -s -C $(LIBS_DIR)/libft
	rsync -a $(LIBS_DIR)/libft/libft.a $(LIBS_DIR)/

$(MLIBX):
	make -s -C $(LIBS_DIR)/mlibx
	rsync -a $(LIBS_DIR)/mlibx/libmlx.a $(LIBS_DIR)/
clean:
	rm -rf $(OBJS_DIR)/*.o
	make clean -s -C $(LIBS_DIR)/libft
	make clean -s -C $(LIBS_DIR)/mlibx
	
fclean:
	rm -rf $(OBJS_DIR)/*.o
	rm -rf $(NAME) $(LIBFT) $(MLIBX)
	make fclean -s -C $(LIBS_DIR)/libft
	make clean -s -C $(LIBS_DIR)/mlibx

re: fclean all

############################################################################


.PHONY: all clean fclean re 