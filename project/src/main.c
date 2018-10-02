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
    }

    copy_buf(&tmp[in_mas->size], in_buf);

    free(in_mas->elem);

    in_mas->elem = tmp;
    in_mas->size++;

    return 0;
}

int str_input(struct buf* tmp_buf) {  // '\0' - 0, '\n' - 1
    char in_char;  // введенный символ

    while ((in_char = getchar()) != EOF) {  // В силайоне не работает поэтому там 'D'
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
        }
    }
    return 0;
}

struct mas_str* parse_str(struct mas_str* in_mas) {
    if (!in_mas) {
        return NULL;
    }

    for (size_t i = 0; i < in_mas->size; i++) {
        if (((strnstr(in_mas->elem[i].str, "Date: ", 6)) != NULL) ||
            ((strnstr(in_mas->elem[i].str, "From: ", 6)) != NULL) ||
            ((strnstr(in_mas->elem[i].str, "To: ", 4)) != NULL) ||
            ((strnstr(in_mas->elem[i].str, "Subject: ", 9)) != NULL)) {

            printf("%s", in_mas->elem[i].str);
        }
    }
    return NULL;
}


int main(void) {
    struct mas_str all_str = {NULL, 0};  // хранит весь ввод
    struct buf tmp_buf = {NULL, 0, 0};  // хранит только одну введенную строку

    while (str_input(&tmp_buf) == 1) {
        add_item(&all_str, &tmp_buf);
        tmp_buf.str = NULL;
        tmp_buf.size = 0;
        tmp_buf.buf_size = 0;
    }

//    for (size_t i = 0; i < all_str.size; i++) {
//        printf("--[%zu]: |", i);
//        printf("%s", all_str.elem[i].str);
//    }

//    printf("\t--results:\n");
    parse_str(&all_str);
//    printf(("END\n"));

    return 0;
}
