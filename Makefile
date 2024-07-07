CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FTPRINTF_DIR = ft_printf
FTPRINTF = $(FTPRINTF_DIR)/libftprintf.a

SRCDIR = srcs
SRCS = $(SRCDIR)/ft_main.c

OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES = -I. -I$(LIBFT_DIR) -I$(FTPRINTF_DIR)
LIB = -lreadline

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB) -o $@ $^

$(LIBFT):
	make -C $(LIBFT_DIR) all

$(FTPRINTF):
	make -C $(FTPRINTF_DIR) all

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB) -o $@ -c $<

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(FTPRINTF_DIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(FTPRINTF_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re