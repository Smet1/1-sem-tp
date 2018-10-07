// From: admin\n
// Subject: hi\n
// Sender: admin\0
// EOF = ctr + D

// TODO(): ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct buf {  // типа строка
    char* str;  // string
    size_t size;  // used mem in char
    size_t capacity;  // capacity
};

void init_buf(struct buf*);  // около конструктор

void free_buf(struct buf*);  // около деструктор

int copy_buf(struct buf*, struct buf*);

struct mas_str {  // массив строк
    struct buf* elem;  // хранимые элементы
    size_t size;  // реал сайз
    size_t capacity;  // капасити
};

void init_mas(struct mas_str*);

void free_mas(struct mas_str*);

int add_item(struct mas_str*, struct buf*);

int str_input(struct buf*);

struct mas_str* parse_str(const struct mas_str*);


int main() {
    struct mas_str all_str;  // хранит весь ввод
    init_mas(&all_str);
    struct buf tmp_buf;  // хранит только одну введенную строку
    init_buf(&tmp_buf);

    int check_input = 0;
    while ((check_input = str_input(&tmp_buf)) == 1) {
        int check_add = 0;
        check_add = add_item(&all_str, &tmp_buf);
        if (check_add) {
            printf("[error]");
            return 0;
        }

        free_buf(&tmp_buf);
    }
    if (check_input == 3) {
        printf("[error]");
        return 0;
    }

    struct mas_str* res = parse_str(&all_str);  // результат парсера
    if (!res) {
        printf("[error]");
        return 0;
    }

    for (size_t i = 0; i < res->size; i++) {
        printf("%s", res->elem[i].str);
    }

    free_buf(&tmp_buf);
    free_mas(&all_str);
    free_mas(res);
    free(res);
    return 0;
}

void init_buf(struct buf* init_buf) {
    init_buf->str = NULL;
    init_buf->size = 0;
    init_buf->capacity = 0;
}

void free_buf(struct buf* free_buf) {
    free(free_buf->str);
    init_buf(free_buf);  // мб не надо, да и выглядит странно, но конструктор зануляет все значения
}

int copy_buf(struct buf* l_buf, struct buf* r_buf) {
    if (!r_buf || !r_buf->str || !l_buf) {
        return 1;
    }

    char* tmp = (char*)malloc((r_buf->size + 1) * sizeof(char));
    if (!tmp) {
        return 1;
    }

    strncpy(tmp, r_buf->str, r_buf->size);
    tmp[r_buf->size] = 0;

    l_buf->str = tmp;
    l_buf->size = r_buf->size;
    l_buf->capacity = r_buf->size;

    return 0;
}

void init_mas(struct mas_str* init_mas) {
    init_mas->elem = NULL;
    init_mas->size = 0;
    init_mas->capacity = 0;
}

void free_mas(struct mas_str* free_mas) {
    for (size_t i = 0; i < free_mas->capacity; i++) {
        free_buf(&free_mas->elem[i]);
    }
    free(free_mas->elem);
    init_mas(free_mas);  // коммент такой же как и в free_buf
}

int add_item(struct mas_str* in_mas, struct buf* in_buf) {
    if (!in_mas || !in_buf) {
        return 1;
    }

    if (in_mas->size + 1 > in_mas->capacity) {
        size_t new_size = (in_mas->capacity * 2) > 4 ? (in_mas->capacity * 2) : 4;  // стандартный размер 4

        in_mas->elem = (struct buf*)realloc(in_mas->elem, (new_size) * (sizeof(struct buf)));
        if (!in_mas->elem) {
            return 1;
        }
        for (size_t i = in_mas->size + 1; i < new_size; i++) {  // зануляю выделенную неиспользованную память
            init_buf(&in_mas->elem[i]);
        }
        in_mas->capacity = new_size;
    }

    int checker = 0;
    checker = copy_buf(&in_mas->elem[in_mas->size], in_buf);  // добавление in_buf в конец
    if (checker) {  // ошибка выполнения copy_buf
        return 1;
    }
    in_mas->size++;

    return 0;
}

int str_input(struct buf* tmp_buf) {  // '\0' - 0, '\n' - 1, [error] - 3
    char in_char;  // введенный символ

    while ((in_char = getchar()) != EOF) {  // В силайоне не работает поэтому там 'D'
        if (tmp_buf->size + 1 > tmp_buf->capacity) {
            size_t new_size = ((tmp_buf->capacity * 2)>(16))?(tmp_buf->capacity * 2):(16);

            tmp_buf->str = (char *)realloc(tmp_buf->str, (new_size + 1) * sizeof(char));
            if (!tmp_buf->str) {
                return 3;
            }
            tmp_buf->capacity = new_size;
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
    if (!result) {
        return NULL;
    }

    init_mas(result);
    int check = 0;
    for (size_t i = 0; i < in_mas->size; i++) {
        if (((strncmp(in_mas->elem[i].str, "Date: ", 6)) == 0) ||
            ((strncmp(in_mas->elem[i].str, "From: ", 6)) == 0) ||
            ((strncmp(in_mas->elem[i].str, "To: ", 4)) == 0) ||
            ((strncmp(in_mas->elem[i].str, "Subject: ", 9)) == 0)) {

            check = add_item(result, &in_mas->elem[i]);
            if (check) {
                return NULL;
            }
        }
    }
    return result;
}
