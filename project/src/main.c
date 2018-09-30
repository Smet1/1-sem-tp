// From: admin\n
// Subject: hi\n
// Sender: admin\0
// EOF = ctr + D
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct mas_str {  // массив строк
    struct buf* elem;
    size_t size;
};

struct buf {  // типа строка
    char* str;  // string
    size_t size;  // used mem in char
    size_t buf_size;  // capacity
};

int main(void) {
    // struct buf my_buf = {NULL, 0, 0};  // хранит весь ввод
    struct buf tmp_buf = {NULL, 0, 0};  // хранит только одну введенную строку
    char in_char;  // введенный символ

    // TODO(): бахнуть весь while в функцию
    while ((in_char = getchar()) != EOF) {
        if (tmp_buf.size + 1 > tmp_buf.buf_size) {
            size_t new_size = !tmp_buf.buf_size ? 1 : tmp_buf.buf_size * 2;

            char *tmp = (char* )malloc((new_size + 1) * sizeof(char));
            if (!tmp) {
                // добавить освобождение памяти в буфере
                printf("[error]\n");
                return 0;
            }
            if (tmp_buf.str) {
                strncpy(tmp, tmp_buf.str, (int)strlen(tmp_buf.str));
                free(tmp_buf.str);
            }

            tmp_buf.str = tmp;
            tmp_buf.buf_size = new_size;
        }
        tmp_buf.str[tmp_buf.size] = in_char;
        tmp_buf.size++;
    }

    printf("out = %s", tmp_buf.str);

    // for (size_t i = 0; (str[i] = getchar()) != EOF; i++) { 

    // }

    // printf("out = %s", str);
    return 0;
}
