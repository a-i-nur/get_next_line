# **************************************************************************** #
#                                   SETTINGS                                   #
# **************************************************************************** #

NAME        = gnl            # имя исполняемого файла
BONUS_NAME  = gnl_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
CPPFLAGS    = -D BUFFER_SIZE=$(BUFFER_SIZE)

# BUFFER_SIZE можно переопределить: make BUFFER_SIZE=100
BUFFER_SIZE ?= 1

# Основные файлы для обязательной части
SRCS        = get_next_line.c get_next_line_utils.c main.c
OBJS        = $(SRCS:.c=.o)

# Бонусные файлы
BONUS_SRCS  = get_next_line_bonus.c get_next_line_utils_bonus.c main.c
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

# **************************************************************************** #
#                                CONVENIENCE                                   #
# **************************************************************************** #

run: $(NAME)
	./$(NAME)

run-sample: $(NAME)
	./$(NAME) sample_input.txt

run-bonus: bonus
	./$(BONUS_NAME)

# **************************************************************************** #
#                              EXTRA / DEBUG RULES                             #
# **************************************************************************** #

# Проверка утечек на macOS (42 обычно так)
leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

leaks2: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) sample_input.txt

# Пример запуска с другим BUFFER_SIZE:
# make re BUFFER_SIZE=1
# make re BUFFER_SIZE=9999

.PHONY: all clean fclean re leaks bonus run run-sample run-bonus
