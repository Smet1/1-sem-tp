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
    char* tmp = (char*)malloc((r_buf->buf_size) * sizeof(char));
    if (!tmp) {
        // добавить освобождение памяти в буфере
        printf("[error]\n");
        return 1;
    }

    strcpy(tmp, r_buf->str);
//    if (l_buf->str) {
//        free(l_buf->str);
//    }

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
    struct buf* tmp = (struct buf*)malloc((in_mas->size + 1) * sizeof(struct buf));

    if (!tmp) {
        // добавить освобождение памяти в буфере
        printf("[error]\n");
        return 0;
    }

    for (size_t i = 0; i < in_mas->size; i++) {
        copy_buf(&tmp[i], &in_mas->elem[i]);

        printf("|%s|\n", tmp[i].str);
    }

    copy_buf(&tmp[in_mas->size], in_buf);

    free(in_mas->elem);

    in_mas->elem = tmp;
    in_mas->size++;

    return 0;
}

int str_input(struct buf* tmp_buf) {  // '\0' - 0, '\n' - 1
    // struct buf tmp_buf = {NULL, 0, 0};  // хранит только одну введенную строку
    char in_char;  // введенный символ

    while ((in_char = getchar()) != EOF) {
        if (tmp_buf->size + 1 > tmp_buf->buf_size) {
            // size_t new_size = !tmp_buf.buf_size ? 1 : tmp_buf.buf_size * 2;
            size_t new_size = ((tmp_buf->buf_size * 2)>(16))?(tmp_buf->buf_size * 2):(16);

            char* tmp = (char*)malloc((new_size + 1) * sizeof(char));
            if (!tmp) {
                // добавить освобождение памяти в буфере
                printf("[error]\n");
                return 0;
            }
            if (tmp_buf->str) {
                strncpy(tmp, tmp_buf->str, (int)strlen(tmp_buf->str));
                free(tmp_buf->str);
            }

            tmp_buf->str = tmp;
            tmp_buf->buf_size = new_size;
        }
        tmp_buf->str[tmp_buf->size] = in_char;
        tmp_buf->size++;

        if (in_char == '\n') {
            return 1;
            // return tmp_buf.str;
        }
    }
    return 0;
}
int main(void) {
    // struct buf my_buf = {NULL, 0, 0};  // хранит весь ввод
    struct mas_str all_str = {NULL, 0};  // хранит весь ввод
    struct buf tmp_buf = {NULL, 0, 0};  // хранит только одну введенную строку

    while (str_input(&tmp_buf) == 1) {
        add_item(&all_str, &tmp_buf);
        tmp_buf.str = NULL;
        tmp_buf.size = 0;
        tmp_buf.buf_size = 0;
    }
    // char in_char;  // введенный символ

    // TODO(): бахнуть весь while в функцию
    // while ((in_char = getchar()) != EOF) {
    //     if (tmp_buf.size + 1 > tmp_buf.buf_size) {
    //         // size_t new_size = !tmp_buf.buf_size ? 1 : tmp_buf.buf_size * 2;
    //         size_t new_size = ((tmp_buf.buf_size * 2)>(16))?(tmp_buf.buf_size * 2):(16);

    //         char* tmp = (char*)malloc((new_size + 1) * sizeof(char));
    //         if (!tmp) {
    //             // добавить освобождение памяти в буфере
    //             printf("[error]\n");
    //             return 0;
    //         }
    //         if (tmp_buf.str) {
    //             strncpy(tmp, tmp_buf.str, (int)strlen(tmp_buf.str));
    //             free(tmp_buf.str);
    //         }

    //         tmp_buf.str = tmp;
    //         tmp_buf.buf_size = new_size;
    //     }
    //     tmp_buf.str[tmp_buf.size] = in_char;
    //     tmp_buf.size++;

    //     if (in_char == '\n') {
    //         printf("out = %s", tmp_buf.str);

    //         int jeppa = add_item(&all_str, &tmp_buf);
    //         printf("add_item = %d\n", jeppa);

    //         // printf("out1 = %s", all_str.elem[all_str.size].str);
    //         // free(tmp_buf.str);
    //     }
    // }
    // ---------------------------------------


    for (size_t i = 0; i < all_str.size; i++) {
        printf("%zu\n", i);
        printf("%s", all_str.elem[i].str);
    }

    return 0;
}
