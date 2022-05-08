#include "command.h"
#include <string.h>

int main(int argc, char* argv[])
{
    if ((argc != 4)
        || (!strcmp(argv[1], "encode")
            && (!strcmp(
                    argv[1],
                    "decode")))) // Проверяем корректность входных аргументов
    {
        printf("Usage:\ncoder encode <in-file-name> <out-file-name>\ncoder "
               "decode <in-file-name> <out-file-name>\n");
        return 0;
    } else {
        if (!strcmp(argv[1], "decode")) // Команда decode декодирует
        {
            decode_file(argv[2], argv[3]);
        } else {
            if (!strcmp(argv[1], "encode")) // Команда encode кодирует
            {
                encode_file(argv[2], argv[3]);
            } else {
                printf("Usage:\ncoder encode <in-file-name> "
                       "<out-file-name>\ncoder decode <in-file-name> "
                       "<out-file-name>\n");
                return 0;
            }
        }
    }
    return 0;
}
