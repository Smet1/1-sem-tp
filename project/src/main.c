// From: admin\n
// Subject: hi\n
// Sender: admin\0
// EOF = ctr + D
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct buf {  // типа строка
    char* str;  // string
    size_t size;  // used mem in char
    size_t buf_size;  // capacity
};

int copy_buf(struct buf* l_buf, struct buf* r_buf) {
    // if (l_buf->str) {
    //     free(l_buf->str);
    // }
    // l_buf->str = r_buf->str;
    char* tmp = (char*)malloc((r_buf->buf_size + 1) * sizeof(char));
    if (!tmp) {
        // добавить освобождение памяти в буфере
        printf("[error]\n");
        return 0;
    }

    strcpy(tmp, r_buf->str);
    free(l_buf->str);
    l_buf->str = tmp;

    l_buf->size = r_buf->size;
    l_buf->buf_size = r_buf->buf_size;
    return 0;
}


struct mas_str {  // массив строк
    struct buf* elem;
    size_t size;
};

int add_item(struct mas_str* in_mas, struct buf* in_buf) {
    struct buf* tmp = (struct buf*)malloc(in_mas->size + 1);
    if (!tmp) {
        // добавить освобождение памяти в буфере
        printf("[error]\n");
        return 0;
    }

    for (size_t i = 0; i < in_mas->size; i++) {
        copy_buf(&tmp[i], &in_mas->elem[i]);
    }
    copy_buf(&tmp[in_mas->size + 1], in_buf);

    free(in_mas->elem);

    in_mas->elem = tmp;

    return 0;
}

int main(void) {
    // struct buf my_buf = {NULL, 0, 0};  // хранит весь ввод
    struct mas_str all_str = {NULL, 0};  // хранит весь ввод
    struct buf tmp_buf = {NULL, 0, 0};  // хранит только одну введенную строку
    char in_char;  // введенный символ

    // TODO(): бахнуть весь while в функцию
    while ((in_char = getchar()) != EOF) {
        if (tmp_buf.size + 1 > tmp_buf.buf_size) {
            // size_t new_size = !tmp_buf.buf_size ? 1 : tmp_buf.buf_size * 2;
            size_t new_size = ((tmp_buf.buf_size * 2)>(16))?(tmp_buf.buf_size * 2):(16);

            char* tmp = (char*)malloc((new_size + 1) * sizeof(char));
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

        if (in_char == '\n') {
            printf("out = %s", tmp_buf.str);
            
            add_item(&all_str, &tmp_buf);
            // free(tmp_buf.str);
        }
    }
    // ---------------------------------------


    for (size_t i = 0; i < all_str.size; i++) {
        printf("%s", all_str.elem[i].str);
    }

    return 0;
}
