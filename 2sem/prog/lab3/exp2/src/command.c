#include "coder.c"
#include <inttypes.h>
#include <stdlib.h>

int encode_file(const char* in_file_name, const char* out_file_name)
{
    //откроем файл для в режиме чтения
    FILE* in = fopen(in_file_name, "r");
    uint32_t b = 0x00100101;
    if (in == NULL)
        return -1;
    //откроем бинарный файл в режиме записи
    FILE* out = fopen(out_file_name, "wb");
    // Если файл не открылся возвращаем -1
    if (out == NULL) {
        fclose(in);
        return -1;
    }
    //Создаем структуру
    CodeUnits* c = malloc(sizeof(CodeUnits));
    uint32_t n;
    while (feof(in) == 0) {
        //считываем число из файла и кодируем
        size_t k = fscanf(in, "%" SCNx32, &n);
        int t = encode(n, c);
        //записываем в бинарный файл закодированое число
        int y = write_code_unit(out, c);
        if (t != 0 || y != 0 || k != 1) {
            free(c);
            fclose(in);
            fclose(out);
            return -1;
        }
    }
    fwrite(&b, 1, sizeof(uint32_t), out);
    write_code_unit(out, c);

    fclose(in);
    fclose(out);
    free(c);
    return 0;
}

int decode_file(const char* in_file_name, const char* out_file_name)
{
    FILE* in = fopen(in_file_name, "rb");
    if (in == NULL)
        return -1;
    FILE* out = fopen(out_file_name, "w");
    if (out == NULL) {
        fclose(in);
        return -1;
    }
    CodeUnits* c = malloc(sizeof(CodeUnits));
    //пока не найдена ошибка в функции
    //декодируем и пишем в файл
    while (read_next_code_unit(in, c) != -1) {
        uint32_t dec = decode(c);
        size_t t = fprintf(out, "\n%" SCNx32, dec);
        // Если не записало число
        if (t == 0) {
            free(c);
            return -1;
        }
    }
    free(c);
    return 0;
}