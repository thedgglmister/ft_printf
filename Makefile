NAME = libftprintf.a

SRCDIR = srcs

OBJDIR = objs

SRCS = $(wildcard $(SRCDIR)/*.c)

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@gcc -Wall -Wextra -Werror -c $< -I includes -o $@

$(NAME): $(OBJS) 
	@ar rc $(NAME) $(OBJS)

.PHONY: clean
clean:
	@rm -f $(OBJS)

.PHONY: flcean
fclean: clean
	@rm -f $(NAME)

.PHONY: re
re: fclean all
