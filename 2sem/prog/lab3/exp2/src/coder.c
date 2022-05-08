#include <stdint.h>
#include <stdio.h>

enum { MaxCodeLength = 4 };

typedef struct {
    uint8_t code[MaxCodeLength];
    size_t length;
} CodeUnits;

int encode(uint32_t code_point, CodeUnits* code_units)
{
    // Считает кол-во бит в числе
    uint32_t r = code_point, count = 0;
    while (r > 0) {
        r = r >> 1;
        count++;
    }
    // Если число меньше 8 бит,то она попадает в 1 октет
    if (count < 8) {
        code_units->length = 1;
        code_units->code[0] = code_point;
    }
    // Если число больше 8, но меньше или равно 11 битам,то она попадает в
    // 2 октета
    if (count > 8 && count <= 11) {
        code_units->length = 2;
        code_units->code[0] = code_units->code[0] | 192; // 11000000
        code_units->code[1] = code_point & 63;           // 00xxxxxx
        code_units->code[1] = code_units->code[1] | 128; // 10xxxxxx
        code_point = code_point >> 6;
        code_units->code[0] = code_units->code[0] | code_point;
    }
    // Если число больше 11, но меньше или равна
    // 1 битам,то она попадает в 3 октета
    if (count > 11 && count <= 16) {
        code_units->length = 3;
        code_units->code[0] = code_units->code[0] | 224; // 11100000
        for (int i = code_units->length - 1; i >= 1; i--) {
            code_units->code[i] = code_point & 63;           // 00xxxxxx
            code_units->code[i] = code_units->code[i] | 128; // 10xxxxxx
            code_point = code_point >> 6;
        }
        code_units->code[0] = code_units->code[0] | code_point;
    }
    // Если число больше 16,но меньше или равна
    // 21 биту,то она попадает в 4 октета
    if (count > 16 && count <= 21) {
        code_units->length = 4;
        code_units->code[0] = code_units->code[0] | 240; // 11110000
        for (int i = code_units->length - 1; i >= 1; i--) {
            code_units->code[i] = code_point & 63;           // 00xxxxxx
            code_units->code[i] = code_units->code[i] | 128; // 10xxxxxx
            code_point = code_point >> 6;
        }
        code_units->code[0] = code_units->code[0] | code_point;
    }
    // Если число превышает больше 21 бита,то она полностью не
    // закодируется и нужно вернуть -1
    if (count > 21)
        return -1;
    return 0;
}

uint32_t decode(const CodeUnits* code_unit)
{
    // Декодируемое число
    uint32_t dec = 0;
    // Если число имеет 1 октет, то декодируемое число
    // становится равным этому числу
    if (code_unit->length == 1)
        dec = code_unit->code[0];
    // Если число имеет 2 октета
    if (code_unit->length == 2) {
        // обнуляем значащие единицы
        // и записываем 1 октет
        dec = code_unit->code[0] & 31; // 00011111
        // сдвигаем на 6 бит вправо,чтобы записать 2 октет
        dec = dec << 6;
        // записываем 2 октет
        dec = dec | (63 & code_unit->code[1]);
    }
    if (code_unit->length == 3) {
        dec = code_unit->code[0] & 15; // 000011111
        // Циклично записываем октеты
        for (size_t i = 1; i < code_unit->length; i++) {
            dec = dec << 6;
            dec = dec | (63 & code_unit->code[i]);
        }
    }
    if (code_unit->length == 4) {
        dec = code_unit->code[0] & 7; // 00000111
        for (size_t i = 1; i < code_unit->length; i++) {
            dec = dec << 6;
            dec = dec | (63 & code_unit->code[i]);
        }
    }
    return dec;
}

int write_code_unit(FILE* out, const CodeUnits* code_unit)
{
    // Циклично записываем байты в файл
    for (size_t i = code_unit->length; i > 0; i--) {
        size_t count = fwrite(
                &code_unit->code[code_unit->length - i],
                1,
                sizeof(uint8_t),
                out);
        if (count != sizeof(uint8_t))
            return -1;
    }
    return 0;
}

int read_next_code_unit(FILE* in, CodeUnits* code_units)
{
    code_units->length = 0;
    uint32_t a = fread(&code_units->code[0], sizeof(uint8_t), 1, in);
    if (a != 1) {
        return -1;
    }
    if (code_units->code[0] < 0x80) {
        code_units->length = 1;
    }
    if (code_units->code[0] < 0xc0) { // 11000000 00000000
        return read_next_code_unit(in, code_units);
    }
    if (code_units->code[0] < 0xf8) {
        code_units->length = 4;
    }
    if (code_units->code[0] < 0xf0) {
        code_units->length = 3;
    }
    if (code_units->code[0] < 0xe0) {
        code_units->length = 2;
    }
    for (size_t i = 1; i < code_units->length; i++) {
        a = fread(&code_units->code[i], sizeof(uint8_t), 1, in);
        if (a != 1) {
            return -1;
        }
        if (code_units->code[i] >> 6 != 2) {
            return read_next_code_unit(in, code_units);
        }
    }

    if (code_units->length == 0) {
        return read_next_code_unit(in, code_units);
    }
    return 0;
}