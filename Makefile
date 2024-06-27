NAME = gnl.exe
SOURCES = get_next_line.c \
		  get_next_line_utils.c \
		  gnl_test_suite.c \
		  ft_strchr.c \
		  ft_strlen.c \
		  ft_memcpy.c \
		  ft_memset.c \
		  ft_itoa.c \
		  ft_substr.c 

BSOURCES =	get_next_line_bonus.c \
			get_next_line_utils.c

YELLOW = \033[33m
GREEN = \033[32m
RESET = \033[0m
BOLD = \033[1m

OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)

AR = ar
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = ranlib

all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $? #Initial compilation of .c files

$(NAME): $(OBJECTS)
	@echo "Creating $(NAME) archive..."
	$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
	@echo "$(YELLOW)Created: $(words $(OBJECTS) ) object file(s)$(RESET)"
	@echo "$(YELLOW)Created: $(NAME)$(RESET)"

clean:
	rm -f $(OBJECTS) $(BOBJECTS) 
	-@rm -f .bonus_made
	@echo "$(GREEN)$(BOLD)SUCCESS$(RESET)"
	@echo "$(YELLOW) Deleted: $(words $(OBJECTS) $(BOBJECTS) $(EOBJECTS)) object file(s)$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(GREEN)SUCCESS$(RESET)"
	@echo "$(YELLOW) Deleted $(words $(NAME)) object files(s)$(RESET)"
	@echo "$(YELLOW) Deleted: $(NAME)"

re: fclean all

so:
	$(CC) -fPIC $(CFLAGS) -c $(SOURCES) $(BSOURCES)
	$(CC) -nostartfiles -shared -o libft.so $(OBJECTS) $(BOBJECTS)


.PHONY: all clean fclean re so
