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
SRCS += $(SRCDIR)/$(ENV)/ft_gen_cmd_env.c

UTILS = utils
SRCS += $(SRCDIR)/$(UTILS)/ft_utils.c
SRCS += $(SRCDIR)/$(UTILS)/get_next_line.c
SRCS += $(SRCDIR)/$(UTILS)/get_next_line_utils.c

BUILIN = builtins
SRCS += $(SRCDIR)/$(BUILIN)/ft_call_builtin.c
SRCS += $(SRCDIR)/$(BUILIN)/ft_cd.c
SRCS += $(SRCDIR)/$(BUILIN)/ft_pwd.c
SRCS += $(SRCDIR)/$(BUILIN)/ft_exit.c

CMD = cmd
SRCS += $(SRCDIR)/$(CMD)/ft_token.c
SRCS += $(SRCDIR)/$(CMD)/ft_cmd_argv.c
SRCS += $(SRCDIR)/$(CMD)/ft_cmds.c
SRCS += $(SRCDIR)/$(CMD)/ft_in_out_fd.c
SRCS += $(SRCDIR)/$(CMD)/ft_cmdinfo_list.c
SRCS += $(SRCDIR)/$(CMD)/ft_heredoc.c
SRCS += $(SRCDIR)/$(CMD)/ft_pipe.c
SRCS += $(SRCDIR)/$(CMD)/ft_signal.c
SRCS += $(SRCDIR)/$(CMD)/ft_static.c
SRCS += $(SRCDIR)/$(CMD)/ft_cmd_line.c
SRCS += $(SRCDIR)/$(CMD)/ft_exe_cmd.c
SRCS += $(SRCDIR)/$(CMD)/ft_redirect.c
SRCS += $(SRCDIR)/$(CMD)/ft_expand_env.c


#OBJS
OBJDIR = objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCDIR = includes

# なぜかrkitaoのmacではこれで実行した方が良さげなので置いておく
# INCLUDES = -I$(SRCDIR) -I$(INCDIR) -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -I$(SRCDIR)/$(UTILS) -I/opt/homebrew/opt/readline/include
# LIB = -lreadline -lncurses -L/opt/homebrew/opt/readline/lib

INCLUDES = -I$(SRCDIR) -I$(INCDIR) -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -I$(SRCDIR)/$(UTILS)
LIB = -lreadline

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIB)

$(LIBFT):
	make -C $(LIBFT_DIR) all

$(FTPRINTF):
	make -C $(FTPRINTF_DIR) all

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(ENV)
	@mkdir -p $(OBJDIR)/$(UTILS)
	@mkdir -p $(OBJDIR)/$(CMD)
	@mkdir -p $(OBJDIR)/$(BUILIN)

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