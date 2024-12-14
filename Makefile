CC := cc
CFLAGS := -Wall -Werror -Wextra

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

FTPRINTF_DIR := ft_printf
FTPRINTF := $(FTPRINTF_DIR)/libftprintf.a

# SRCS
SRCDIR := srcs
SRCS += $(SRCDIR)/ft_main.c

ENV := env
SRCS += $(SRCDIR)/$(ENV)/ft_env.c
SRCS += $(SRCDIR)/$(ENV)/ft_path.c
SRCS += $(SRCDIR)/$(ENV)/ft_search_env.c
SRCS += $(SRCDIR)/$(ENV)/ft_gen_cmd_env.c
SRCS += $(SRCDIR)/$(ENV)/ft_show_env_list.c
SRCS += $(SRCDIR)/$(ENV)/ft_free_env_list.c

UTILS := utils
SRCS += $(SRCDIR)/$(UTILS)/ft_utils1.c
SRCS += $(SRCDIR)/$(UTILS)/ft_utils2.c
SRCS += $(SRCDIR)/$(UTILS)/get_next_line.c
SRCS += $(SRCDIR)/$(UTILS)/get_next_line_utils.c
SRCS += $(SRCDIR)/$(UTILS)/ft_static.c

BUILIN := builtins
SRCS += $(SRCDIR)/$(BUILIN)/ft_call_builtin.c
SRCS += $(SRCDIR)/$(BUILIN)/ft_cd.c
SRCS += $(SRCDIR)/$(BUILIN)/ft_pwd.c
SRCS += $(SRCDIR)/$(BUILIN)/ft_exit.c
SRCS += $(SRCDIR)/$(BUILIN)/ft_env.c
SRCS += $(SRCDIR)/$(BUILIN)/ft_echo.c
SRCS += $(SRCDIR)/$(BUILIN)/ft_export.c
SRCS += $(SRCDIR)/$(BUILIN)/ft_unset.c

PRE_CMD := pre_cmd
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_ambiguous_redirect.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_cmd_argv.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_cmd_argv2.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_cmdinfo_list.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_cmds.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_in_out_fd.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_token.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_heredoc.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_exec_heredoc.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_heredoc_limiter.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_expand_env.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_redirect.c
SRCS += $(SRCDIR)/$(PRE_CMD)/ft_split_after_index.c

CMD := cmd
SRCS += $(SRCDIR)/$(CMD)/ft_pipe.c
SRCS += $(SRCDIR)/$(CMD)/ft_signal.c
SRCS += $(SRCDIR)/$(CMD)/ft_cmd_line.c
SRCS += $(SRCDIR)/$(CMD)/ft_exe_cmd.c
SRCS += $(SRCDIR)/$(CMD)/ft_exe_cmd_childp.c

#OBJS
OBJDIR := objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%$(SUFFIX).o)

# コンパイルオプション
INCDIR := includes
INCLUDES := -I$(SRCDIR) -I$(INCDIR) -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -I$(SRCDIR)/$(UTILS)
LIB := -lreadline

# 実行ファイル名
NAME = $(PJT)$(SUFFIX)

# プロジェクト名
PJT := minishell

# SUFFIX一覧
SUFFIXES := _both _rkitao _yyamasak

# デバッグの場合分け
ifdef BOTH_DEBUG
	DEFINES := -D RKITAO_DEBUG -D YYAMASAK_DEBUG
	SUFFIX := $(word 1, $(SUFFIXES))
else ifdef RKITAO_DEBUG
	DEFINES := -D RKITAO_DEBUG
	SUFFIX := $(word 2, $(SUFFIXES))
else ifdef YYAMASAK_DEBUG
	DEFINES := -D YYAMASAK_DEBUG
	SUFFIX := $(word 3, $(SUFFIXES))
else
	DEFINES :=
	SUFFIX :=
endif

# ターゲット
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIB)

rkitao:
	make RKITAO_DEBUG=1

yyamasak:
	make YYAMASAK_DEBUG=1

both:
	make BOTH_DEBUG=1

$(LIBFT):
	make -C $(LIBFT_DIR) all

$(FTPRINTF):
	make -C $(FTPRINTF_DIR) all

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(ENV)
	@mkdir -p $(OBJDIR)/$(UTILS)
	@mkdir -p $(OBJDIR)/$(CMD)
	@mkdir -p $(OBJDIR)/$(PRE_CMD)
	@mkdir -p $(OBJDIR)/$(BUILIN)

$(OBJDIR)/%$(SUFFIX).o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -o $@ -c $<

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(FTPRINTF_DIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(PJT)
	rm -f $(foreach SUFFIX,$(SUFFIXES),$(NAME))
	make -C $(LIBFT_DIR) fclean
	make -C $(FTPRINTF_DIR) fclean

re: fclean all

.PHONY: all bonus rkitao yyamasak both clean fclean re