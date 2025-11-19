#include "get_next_line.h"
#include <fcntl.h>   // open
#include <unistd.h>  // close, read
#include <stdio.h>   // printf, perror
#include <stdlib.h>  // free

/*
 * Функция для чтения и печати всех строк из заданного fd.
 * name используется только для красивого вывода (имя файла или "stdin").
 */
static void  read_from_fd(int fd, const char *name)
{
    char    *line;
    int     line_num = 1;

    printf("===== Чтение из: %s =====\n", name);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("[%s][%d]: %s", name, line_num, line);
        // если строка не заканчивается \n, добавим перевод строки для красоты
        if (line[0] != '\0' && line[ft_strlen(line) - 1] != '\n')
            printf("\n");
        free(line);
        line_num++;
    }
    printf("===== Конец: %s =====\n\n", name);
}

int main(int argc, char **argv)
{
    int fd;
    int i;

    // Если аргументов нет — читаем из stdin (fd = 0)
    if (argc == 1)
    {
        printf("Режим чтения из stdin.\n");
        printf("Печатай строки и нажимай Enter.\n");
        printf("Чтобы закончить ввод, нажми Ctrl+D (EOF).\n\n");
        read_from_fd(0, "stdin");
        return 0;
    }

    // Если есть аргументы — каждый аргумент считаем файлом
    i = 1;
    while (i < argc)
    {
        fd = open(argv[i], O_RDONLY);
        if (fd < 0)
        {
            perror(argv[i]);
        }
        else
        {
            read_from_fd(fd, argv[i]);
            close(fd);
        }
        i++;
    }
    return 0;
}
