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
    if (!r_buf || !r_buf->str || !l_buf) {
        printf("!r_buf || !r_buf->str || !l_buf\n");
        return 1;
    }

    char* tmp = (char*)malloc((r_buf->size + 1) * sizeof(char));
    if (!tmp) {
        printf("[error]\n");
        return 1;
    }

    strncpy(tmp, r_buf->str, r_buf->size);
    tmp[r_buf->size] = 0;
    l_buf->str = tmp;

    tmp = NULL;
    l_buf->size = r_buf->size;
    l_buf->buf_size = r_buf->size;

    return 0;
}


struct mas_str {  // массив строк
    struct buf* elem;  // хранимые элементы
    size_t size;  // реал сайз
    size_t mas_size;  // капасити
};

int add_item(struct mas_str* in_mas, struct buf* in_buf) {
    if (in_mas->size + 1 > in_mas->mas_size) {
        size_t new_size = (in_mas->mas_size * 2) > 5 ? (in_mas->mas_size * 2) : 5;  // стандартный размер 5

        struct buf* tmp = (struct buf*)malloc((new_size) * sizeof(struct buf));
        if (!tmp) {
            printf("[error]\n");
            return 1;
        }
        for (size_t i = 0; i < in_mas->size; i++) {
            copy_buf(&tmp[i], &in_mas->elem[i]);
            free(in_mas->elem[i].str);
        }

        for (size_t i = in_mas->size + 1; i < new_size; i++) {  // зануляю выделенную неиспользованную память
            tmp[i].str = NULL;
//            tmp[i].size = 0;
//            tmp[i].buf_size = 0;
        }

        in_mas->mas_size = new_size;
        in_mas->elem = tmp;
    }

    copy_buf(&in_mas->elem[in_mas->size], in_buf);  // добавление in_buf в конец
    in_mas->size++;

    return 0;
}

int str_input(struct buf* tmp_buf) {  // '\0' - 0, '\n' - 1
    char in_char;  // введенный символ

    while ((in_char = getchar()) != EOF) {  // В силайоне не работает поэтому там 'D'
        if (tmp_buf->size + 1 > tmp_buf->buf_size) {
            // size_t new_size = !tmp_buf.buf_size ? 1 : tmp_buf.buf_size * 2;
            size_t new_size = ((tmp_buf->buf_size * 2)>(16))?(tmp_buf->buf_size * 2):(16);

            // TODO(): new_size + 1 ?? добавлять ли символ конца строки
            char* tmp = (char*)malloc((new_size + 1) * sizeof(char));
            if (!tmp) {
                printf("[error]\n");
                return 1;
            }

            if (tmp_buf->str) {
                strncpy(tmp, tmp_buf->str, tmp_buf->size);
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

struct mas_str* parse_str(const struct mas_str* in_mas) {
    if (!in_mas) {
        return NULL;
    }

    struct mas_str* result = (struct mas_str*)malloc(1 * sizeof(struct mas_str));
    result->mas_size = 0;
    result->size = 0;

    for (size_t i = 0; i < in_mas->size; i++) {
        if (((strstr(in_mas->elem[i].str, "Date: ")) != NULL) ||
            ((strstr(in_mas->elem[i].str, "From: ")) != NULL) ||
            ((strstr(in_mas->elem[i].str, "To: ")) != NULL) ||
            ((strstr(in_mas->elem[i].str, "Subject: ")) != NULL)) {

            add_item(result, &in_mas->elem[i]);
        }
    }
    return result;
}


int main() {
    struct mas_str all_str = {NULL, 0, 0};  // хранит весь ввод
    struct buf tmp_buf = {NULL, 0, 0};  // хранит только одну введенную строку

    while (str_input(&tmp_buf) == 1) {
        add_item(&all_str, &tmp_buf);

        free(tmp_buf.str);

        tmp_buf.str = NULL;
        tmp_buf.size = 0;
        tmp_buf.buf_size = 0;
    }

    struct mas_str* res = parse_str(&all_str);  // результат парсера
    // TODO(): написать метод free_? для всех структур
    // beg
    for (size_t i = 0; i < res->size; i++) {
        printf("%s", res->elem[i].str);
    }

    for (size_t i = 0; i < all_str.size; i++) {
        free(all_str.elem[i].str);
    }
    free(all_str.elem);

    free(tmp_buf.str);

    for (size_t i = 0; i < all_str.mas_size; i++) {
        free(res->elem[i].str);
    }
    free(res->elem);
    free(res);
    // end
    return 0;
}
