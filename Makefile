# **************************************************************************** #
#                                   SETTINGS                                   #
# **************************************************************************** #

NAME        = gnl            # имя исполняемого файла
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# BUFFER_SIZE можно переопределить: make BUFFER_SIZE=100
BUFFER_SIZE ?= 42

# Основные файлы для обязательной части
SRCS        = get_next_line.c get_next_line_utils.c main.c
OBJS        = $(SRCS:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) $(OBJS) -o $(NAME)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# **************************************************************************** #
#                              EXTRA / DEBUG RULES                             #
# **************************************************************************** #

# Проверка утечек на macOS (42 обычно так)
leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

# Пример запуска с другим BUFFER_SIZE:
# make re BUFFER_SIZE=1
# make re BUFFER_SIZE=9999

.PHONY: all clean fclean re leaks
