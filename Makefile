
NAME = 21sh

CC = gcc

SRCDIR = srcs

FLAGS = -Wall -Werror -Wextra -g

SRCS =  main.c term.c ed.c env.c touch.c print_shell.c treatmt.c t.c exec.c \
ctrl.c tools.c init.c parsing.c prompt.c giv_str.c pascutcopy.c \
parsing_type.c parsing_type_fct.c parsing_tools.c free.c redirecting.c \

SRC_N = $(addprefix $(SRCDIR)/, $(SRCS))

OBJDIR = objs

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT= -L./libft/ -lft

all : $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	$(CC) $(OBJS) $(LIBFT) $(FLAGS) -o $(NAME) -ltermcap -g

${OBJDIR}/%.o: srcs/%.c
	@mkdir -p ${OBJDIR}
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	make -C ./libft/ clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make -C ./libft/ fclean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
