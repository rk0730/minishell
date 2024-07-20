CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FTPRINTF_DIR = ft_printf
FTPRINTF = $(FTPRINTF_DIR)/libftprintf.a

# SRCS
SRCDIR = srcs
SRCS += $(SRCDIR)/ft_main.c

ENV = env
SRCS += $(SRCDIR)/$(ENV)/ft_env.c
SRCS += $(SRCDIR)/$(ENV)/ft_path.c
SRCS += $(SRCDIR)/$(ENV)/ft_search_env.c

UTILS = utils
SRCS += $(SRCDIR)/$(UTILS)/ft_utils.c

CMD = cmd
SRCS += $(SRCDIR)/$(CMD)/ft_exe_cmd.c
SRCS += $(SRCDIR)/$(CMD)/ft_token.c
SRCS += $(SRCDIR)/$(CMD)/ft_cmd_array.c
SRCS += $(SRCDIR)/$(CMD)/ft_out_fd.c
SRCS += $(SRCDIR)/$(CMD)/ft_in_fd.c
SRCS += $(SRCDIR)/$(CMD)/ft_heredoc.c


#OBJS
OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCDIR = includes

INCLUDES = -I$(SRCDIR) -I$(INCDIR) -I$(LIBFT_DIR) -I$(FTPRINTF_DIR)
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
	@mkdir -p $(OBJDIR)/$(ENV)
	@mkdir -p $(OBJDIR)/$(UTILS)
	@mkdir -p $(OBJDIR)/$(CMD)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

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