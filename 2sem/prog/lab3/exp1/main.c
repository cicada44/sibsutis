#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000

uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90) {
        return r % 128;
    }
    if (p < 95) {
        return r % 16384;
    }
    if (p < 99) {
        return r % 2097152;
    }
    return r % 268435455;
}

void print_bin(uint32_t x)
{
    for (int i = 31; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
        if (i % 8 == 0)
            printf(" ");
    }
    printf("\n");
}

size_t encode_varint(uint32_t value, uint8_t* buf)
{
    assert(buf != NULL);
    uint8_t* cur = buf;
    while (value >= 0x80) {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}

uint32_t decode_varint(const uint8_t** bufp)
{
    const uint8_t* cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

int main()
{
    int lenCompr, lenUncompr, genVal;
    FILE *fUncW, *fUncR, *fCompr;
    unsigned int i;
    size_t encval;
    uint8_t c;
    unsigned int arrUnc[N], arrCompr[N];

    //Открываем файл на битовую запись и записываем в указатель fUnc
    fUncW = fopen("uncompressed.dat", "wb");

    //Генерируем случайные числа и записываем побитово в uncompressed.dat
    for (int j = 0; j < N; j++) {
        i = generate_number();
        arrUnc[j] = i;
        fwrite(&i, 8, 1, fUncW);
    }
    lenUncompr = ftell(fUncW);
    fclose(fUncW);

    //Открываем файл с числами в несжатом виде и файл для varintа
    fUncR = fopen("uncompressed.dat", "rb");
    fCompr = fopen("compressed.dat", "wb");

    //Считываем байты из файла с несжатыми числами и записываем в файл с varint
    for (int j = 0; j < N; j++) {
        fread(&i, 8, 1, fUncR);
        encval = encode_varint(i, &c);
        fwrite(&c, encval, 1, fCompr);
    }
    fclose(fCompr);
    fclose(fUncR);

    //Заполняем массив значениями из сжатого файла
    fCompr = fopen("compressed.dat", "rb");
    fseek(fCompr, 0, 2);
    lenCompr = ftell(fCompr);
    uint8_t* arr = (unsigned char*)malloc(sizeof(uint8_t) * lenCompr);
    fseek(fCompr, 0, 0);
    fread(arr, lenCompr, 1, fCompr);
    fclose(fCompr);

    const uint8_t* temp = arr;
    for (int j = 0; j < N; j++)
        arrCompr[j] = decode_varint(&temp);
    printf("EXAMPLE VALUES:\n\n");
    for (int i = 0; i < 5; i++) {
        genVal = generate_number();
        if (arrUnc[genVal] != arrCompr[genVal]) {
            printf("НЕСОВПАДАЮТ ЗНАЧЕНИЯ ИСХОДНОГО И ЗАКОДИРОВАННОГО ЧИСЛА\n");
            return 0;
        }
        printf("Uncompresed value - %d\tCompessed value - %d\n",
               arrUnc[genVal],
               arrCompr[genVal]);
    }
    printf("\nlenght of compressed file - %d\n", lenCompr);
    printf("lenght of uncompressed file - %d\n", lenUncompr);
    printf("\nUncompressed file more about %d times than compressed file\n",
           lenUncompr / lenCompr);

    return 0;
}